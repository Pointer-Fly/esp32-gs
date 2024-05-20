#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "esp_wifi.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "protocol_examples_common.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"

#include "lwip/sockets.h"
#include "lwip/dns.h"
#include "lwip/netdb.h"

#include "esp_log.h"
#include "mqtt_client.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>

#include "nvs_flash.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
// #include "esp_wifi.h"

#include "nvs_flash.h"
#include "esp_netif.h"

#include "esp_event.h"
#include "freertos/event_groups.h"
#include "esp_timer.h"
// #include "esp_event_loop.h"

#include "st7789.h"

#include "gpio_button.h"

// #include "lv_demos.h"
#include "../lvgl.h"
#include "ui.h"
// #include <time.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/mcpwm_prelude.h"

#include "st7789.h"
#include "gpio_button.h"
#include "../lvgl.h"
#include "ui.h"
#include <time.h>
#include "HX711.h"

static const char *TAG = "main";
// Please consult the datasheet of your servo before changing the following parameters
#define SERVO_MIN_PULSEWIDTH_US 500  // Minimum pulse width in microsecond
#define SERVO_MAX_PULSEWIDTH_US 2500 // Maximum pulse width in microsecond
#define SERVO_MIN_DEGREE -90         // Minimum angle
#define SERVO_MAX_DEGREE 90          // Maximum angle

#define SERVO_PULSE_GPIO 7                   // GPIO connects to the PWM signal line
#define SERVO_TIMEBASE_RESOLUTION_HZ 1000000 // 1MHz, 1us per tick
#define SERVO_TIMEBASE_PERIOD 20000          // 20000 ticks, 20ms

int angle;
int step;
mcpwm_oper_handle_t oper = NULL;
mcpwm_timer_handle_t timer = NULL;
mcpwm_cmpr_handle_t comparator = NULL;
int buf[100] = {0};
int weight_Thresold = 20;
int hw_1_Flag = 0;
int hw_2_Flag = 0;
int weight_Flag = 0;

#define SEND_TOPIC "/order/gs/send" // 发送的主题
#define RECV_TOPIC "/order/gs/recv" // 接收的主题

void message_deal(const char *topic, const char *data, const int topic_len, const int data_len);
void report_weight_task(void *pvParameters);

static void log_error_if_nonzero(const char *message, int error_code)
{
    if (error_code != 0) {
        ESP_LOGE(TAG, "Last error %s: 0x%x", message, error_code);
    }
}

/*
 * @brief Event handler registered to receive MQTT events
 *
 *  This function is called by the MQTT client event loop.
 *
 * @param handler_args user data registered to the event.
 * @param base Event base for the handler(always MQTT Base in this example).
 * @param event_id The id for the received event.
 * @param event_data The data for the event, esp_mqtt_event_handle_t.
 */
static void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data)
{
    ESP_LOGD(TAG, "Event dispatched from event loop base=%s, event_id=%" PRIi32 "", base, event_id);
    esp_mqtt_event_handle_t event = event_data;
    esp_mqtt_client_handle_t client = event->client;
    int msg_id;
    switch ((esp_mqtt_event_id_t)event_id) {
    case MQTT_EVENT_CONNECTED:
        ESP_LOGI(TAG, "MQTT_EVENT_CONNECTED");
        // msg_id = esp_mqtt_client_publish(client, "/topic/qos1", "data_3", 0, 1, 0);
        // ESP_LOGI(TAG, "sent publish successful, msg_id=%d", msg_id);

        msg_id = esp_mqtt_client_subscribe(client, RECV_TOPIC, 0);
        ESP_LOGI(TAG, "sent subscribe successful, msg_id=%d", msg_id);

        break;
    case MQTT_EVENT_DISCONNECTED:
        ESP_LOGI(TAG, "MQTT_EVENT_DISCONNECTED");
        break;

    case MQTT_EVENT_SUBSCRIBED:
        // ESP_LOGI(TAG, "MQTT_EVENT_SUBSCRIBED, msg_id=%d", event->msg_id);
        // msg_id = esp_mqtt_client_publish(client, "/topic/qos0", "data", 0, 0, 0);
        // ESP_LOGI(TAG, "sent publish successful, msg_id=%d", msg_id);
        break;
    case MQTT_EVENT_UNSUBSCRIBED:
        ESP_LOGI(TAG, "MQTT_EVENT_UNSUBSCRIBED, msg_id=%d", event->msg_id);
        break;
    case MQTT_EVENT_PUBLISHED:
        ESP_LOGI(TAG, "MQTT_EVENT_PUBLISHED, msg_id=%d", event->msg_id);
        break;
    case MQTT_EVENT_DATA:
        ESP_LOGI(TAG, "MQTT_EVENT_DATA");
        // printf("TOPIC=%.*s\r\n", event->topic_len, event->topic);
        // printf("DATA=%.*s\r\n", event->data_len, event->data);
        message_deal(event->topic, event->data, event->topic_len, event->data_len);
        break;
    case MQTT_EVENT_ERROR:
        ESP_LOGI(TAG, "MQTT_EVENT_ERROR");
        if (event->error_handle->error_type == MQTT_ERROR_TYPE_TCP_TRANSPORT) {
            log_error_if_nonzero("reported from esp-tls", event->error_handle->esp_tls_last_esp_err);
            log_error_if_nonzero("reported from tls stack", event->error_handle->esp_tls_stack_err);
            log_error_if_nonzero("captured as transport's socket errno",  event->error_handle->esp_transport_sock_errno);
            ESP_LOGI(TAG, "Last errno string (%s)", strerror(event->error_handle->esp_transport_sock_errno));

        }
        break;
    default:
        ESP_LOGI(TAG, "Other event id:%d", event->event_id);
        break;
    }
}

static void mqtt_app_start(void)
{
    esp_mqtt_client_config_t mqtt_cfg = {
        .broker.address.uri = CONFIG_BROKER_URL,
    };

    esp_mqtt_client_handle_t client = esp_mqtt_client_init(&mqtt_cfg);
    /* The last argument may be used to pass data to the event handler, in this example mqtt_event_handler */
    esp_mqtt_client_register_event(client, ESP_EVENT_ANY_ID, mqtt_event_handler, NULL);
    esp_mqtt_client_start(client);
    xTaskCreate(report_weight_task, "report_weight_task", 4096, client, 10, NULL);
}

void message_deal(const char *topic, const char *data, const int topic_len, const int data_len)
{
    if (strncmp(topic, RECV_TOPIC, topic_len) == 0) {
        if (strncmp(data, "open", data_len) == 0) {
            servo_up();
        } else if (strncmp(data, "close", data_len) == 0) {
            servo_down();
        }else if(strncmp(data, "w+", data_len) == 0){
            ESP_LOGI(TAG, "weight++");
        }else if(strncmp(data, "w-", data_len) == 0){
            ESP_LOGI(TAG, "weight--");
        }
    }
}

void report_weight_task(void *pvParameters)
{
    esp_mqtt_client_handle_t client = (esp_mqtt_client_handle_t)pvParameters;
    while (1) {
        vTaskDelay(5000 / portTICK_PERIOD_MS);
        char *weight_report = (char *)malloc(100);
        sprintf(weight_report, "weight: %d", weight_real);
        esp_mqtt_client_publish(client, SEND_TOPIC, weight_report, 0, 0, 0);
        free(weight_report);
    }
}





static inline uint32_t example_angle_to_compare(int angle)
{
    return (angle - SERVO_MIN_DEGREE) * (SERVO_MAX_PULSEWIDTH_US - SERVO_MIN_PULSEWIDTH_US) / (SERVO_MAX_DEGREE - SERVO_MIN_DEGREE) + SERVO_MIN_PULSEWIDTH_US;
}

void servo_init(void)
{
    ESP_LOGI(TAG, "Create timer and operator");

    mcpwm_timer_config_t timer_config = {
        .group_id = 0,
        .clk_src = MCPWM_TIMER_CLK_SRC_DEFAULT,
        .resolution_hz = SERVO_TIMEBASE_RESOLUTION_HZ,
        .period_ticks = SERVO_TIMEBASE_PERIOD,
        .count_mode = MCPWM_TIMER_COUNT_MODE_UP,
    };
    ESP_ERROR_CHECK(mcpwm_new_timer(&timer_config, &timer));

    mcpwm_operator_config_t operator_config = {
        .group_id = 0, // operator must be in the same group to the timer
    };
    ESP_ERROR_CHECK(mcpwm_new_operator(&operator_config, &oper));

    ESP_LOGI(TAG, "Connect timer and operator");
    ESP_ERROR_CHECK(mcpwm_operator_connect_timer(oper, timer));

    ESP_LOGI(TAG, "Create comparator and generator from the operator");

    mcpwm_comparator_config_t comparator_config = {
        .flags.update_cmp_on_tez = true,
    };
    ESP_ERROR_CHECK(mcpwm_new_comparator(oper, &comparator_config, &comparator));

    mcpwm_gen_handle_t generator = NULL;
    mcpwm_generator_config_t generator_config = {
        .gen_gpio_num = SERVO_PULSE_GPIO,
    };
    ESP_ERROR_CHECK(mcpwm_new_generator(oper, &generator_config, &generator));

    // set the initial compare value, so that the servo will spin to the center position
    ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(comparator, example_angle_to_compare(0)));

    ESP_LOGI(TAG, "Set generator action on timer and compare event");
    // go high on counter empty
    ESP_ERROR_CHECK(mcpwm_generator_set_action_on_timer_event(generator,
                                                              MCPWM_GEN_TIMER_EVENT_ACTION(MCPWM_TIMER_DIRECTION_UP, MCPWM_TIMER_EVENT_EMPTY, MCPWM_GEN_ACTION_HIGH)));
    // go low on compare threshold
    ESP_ERROR_CHECK(mcpwm_generator_set_action_on_compare_event(generator,
                                                                MCPWM_GEN_COMPARE_EVENT_ACTION(MCPWM_TIMER_DIRECTION_UP, comparator, MCPWM_GEN_ACTION_LOW)));

    ESP_LOGI(TAG, "Enable and start timer");
    ESP_ERROR_CHECK(mcpwm_timer_enable(timer));
    ESP_ERROR_CHECK(mcpwm_timer_start_stop(timer, MCPWM_TIMER_START_NO_STOP));

    angle = 0;
    step = 2;
}

void servo_set()
{
    // /****
    //  * 舵机打角
    ESP_LOGI(TAG, "Angle of rotation: %d", angle);
    ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(comparator, example_angle_to_compare(angle)));
    // Add delay, since it takes time for servo to rotate, usually 200ms/60degree rotation under 5V power supply
    vTaskDelay(pdMS_TO_TICKS(500));
    if ((angle + step) > 60 || (angle + step) < -60)
    {
        step *= -1;
    }
    angle += step;
    // */
}

void servo_up()
{
    //  * 舵机打角 抬杆
    angle = 10;
    ESP_LOGI(TAG, "Angle of rotation: %d", angle);
    ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(comparator, example_angle_to_compare(angle)));
    // Add delay, since it takes time for servo to rotate, usually 200ms/60degree rotation under 5V power supply
    vTaskDelay(pdMS_TO_TICKS(500));
    angle = 10;
}

void servo_down()
{
    //  * 舵机打角 抬杆
    angle = 30;
    ESP_LOGI(TAG, "Angle of rotation: %d", angle);
    ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(comparator, example_angle_to_compare(angle)));
    // Add delay, since it takes time for servo to rotate, usually 200ms/60degree rotation under 5V power supply
    vTaskDelay(pdMS_TO_TICKS(500));
    angle = 30;
}

void app_main(void)
{
    esp_log_level_set("*", ESP_LOG_INFO);
    esp_log_level_set("mqtt_client", ESP_LOG_VERBOSE);
    esp_log_level_set("MQTT_EXAMPLE", ESP_LOG_VERBOSE);
    esp_log_level_set("TRANSPORT_BASE", ESP_LOG_VERBOSE);
    esp_log_level_set("esp-tls", ESP_LOG_VERBOSE);
    esp_log_level_set("TRANSPORT", ESP_LOG_VERBOSE);
    esp_log_level_set("outbox", ESP_LOG_VERBOSE);

    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    /* This helper function configures Wi-Fi or Ethernet, as selected in menuconfig.
     * Read "Establishing Wi-Fi or Ethernet Connection" section in
     * examples/protocols/README.md for more information about this function.
     */
    ESP_ERROR_CHECK(example_connect());

    mqtt_app_start();

    st7789_init();
    Init_HX711();
    gpio_button_init();
    servo_init();
    // 差屏幕、压力
    ui_init();

    weight_first = ReadCount(); // 读取首次数据

    servo_down();
    while (1)
    {

        // 当压力和第一个红外 抬起
        if (hw_1_Flag == 0 && hw_2_Flag == 1)
        {
            servo_up();
        }
        // 当两个红外+压力：收费阶段
        if (weight_real > weight_Thresold)
        {
            gpio_set_level(2, 0);
            vTaskDelay(pdMS_TO_TICKS(100));
            gpio_set_level(2, 1);
        }

        // （当两个红外+压力 --> 只有一个红外无压力） 离开阶段
        if (hw_1_Flag == 1 && hw_2_Flag == 0)
        {
            servo_down();
        }

        // 参数调整阈值
        int a = gpio_get_level(15);
        if (a == 0)
        {
            weight_Thresold++;
            printf("重量阈值增加：%u\r\n", weight_Thresold);
        }
        int b = gpio_get_level(18);
        if (b == 0)
        {
            weight_Thresold--;
            printf("重量阈值减少：%u\r\n", weight_Thresold);
        }

        // 红外1
        hw_1_Flag = gpio_get_level(8);
        printf("红外1 = %d\r\n", hw_1_Flag);
        // 红外2
        hw_2_Flag = gpio_get_level(6);
        printf("红外2 = %d\r\n", hw_2_Flag);

        // 压力传感器
        WeightReal(); // 读取重量

        // 显示重量
        lv_arc_set_value(ui_heightArc, (int16_t)weight_real);
        sprintf(buf, "%lug", weight_real);
        lv_label_set_text(ui_heightLabel, buf);
        // 显示重量阈值
        lv_arc_set_value(ui_shiduArc, weight_Thresold);
        sprintf(buf, "%ug", weight_Thresold);
        lv_label_set_text(ui_shiduLabel, buf);

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
