//
// Created by Monee on 2024/4/24.
//

#ifndef BLINK_HX711_H
#define BLINK_HX711_H
#include "stdio.h"
#include "driver/gpio.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#define HX711_SCK 4  // GPIO number for SCK pin
#define HX711_DOUT 5 // GPIO number for DOUT pin

extern uint32_t Weight;
extern uint32_t weight_first;
extern uint32_t weight_real;

uint32_t ReadCount(void);
uint32_t WeightReal(void);
void Init_HX711(void);
#endif // BLINK_HX711_H
