//
// Created by Monee on 2024/4/24.
//
/************************************************************************************

*************************************************************************************/
#include "HX711.h"
#include "freertos/task.h"
#define HX711_SCK_GPIO 4
#define HX711_DOUT_GPIO 5

#define SDA_PIN 5
#define SCL_PIN 4
#define HX711_DOUT_GPIO_PIN 5
#define HX711_SCK_GPIO_PIN 4

uint32_t Weight = 0;
uint32_t weight_first = 0;
uint32_t weight_real = 0;

uint32_t ReadCount(void)
{
    uint32_t Count = 0;
    uint8_t i = 0;
    vTaskDelay(10 / portTICK_PERIOD_MS);
    gpio_set_level(HX711_SCK_GPIO_PIN, 0);

    while (gpio_get_level(HX711_DOUT_GPIO_PIN))
        ; // 等待DOUT为低电平
    for (i = 0; i < 24; i++)
    {
        gpio_set_level(HX711_SCK_GPIO_PIN, 1);
        Count = Count << 1;
        if (gpio_get_level(HX711_DOUT_GPIO_PIN))
        {
            Count++;
        }
        gpio_set_level(HX711_SCK_GPIO_PIN, 0);
    }

    gpio_set_level(HX711_SCK_GPIO_PIN, 1);
    Count = Count ^ 0x800000;
    gpio_set_level(HX711_SCK_GPIO_PIN, 0);
    return Count;
}

uint32_t WeightReal(void)
{
    weight_real = ReadCount();
    if (weight_first >= weight_real)
    {
        weight_real = weight_first - weight_real;
        weight_real = weight_real / 100;
        // printf("Weight: %lu g\n", weight_real);
    }
    else
    {
        weight_real = weight_real - weight_first;
        weight_real = weight_real / 100;
        // printf("Weight: -%lu \n", weight_real);
    }
    weight_real = weight_real / 100;
    return weight_real;
}
void Init_HX711(void)
{
    gpio_config_t io_conf;

    // Configuration for HX711_SCK (GPIO0) as push-pull output
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = (1ULL << HX711_SCK_GPIO);
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);

    // Configuration for HX711_DOUT (GPIO1) as input with pull-up
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pin_bit_mask = (1ULL << HX711_DOUT_GPIO);
    io_conf.pull_down_en = 0; // Disable pull-down resistor
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);

    // Configuration for HX711_DOUT (GPIO1) as input with pull-up
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pin_bit_mask = (1ULL << 8);
    io_conf.pull_down_en = 0; // Disable pull-down resistor
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);

    // Configuration for HX711_DOUT (GPIO1) as input with pull-up
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pin_bit_mask = (1ULL << 6);
    io_conf.pull_down_en = 0; // Disable pull-down resistor
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);

    // Configuration for HX711_SCK (GPIO0) as push-pull output
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = (1ULL << 2);
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);

    gpio_set_level(HX711_SCK_GPIO, 0); // Initialize HX711_SCK to low level
}
