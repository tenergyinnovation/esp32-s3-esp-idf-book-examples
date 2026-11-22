#pragma once
#include "driver/gpio.h"
#include "esp_err.h"

typedef enum { TL_OFF, TL_RED, TL_YELLOW, TL_GREEN } tl_state_t;

typedef struct {
    gpio_num_t red, yellow, green;
    tl_state_t state;
} traffic_light_t;

esp_err_t traffic_light_init(traffic_light_t *tl, gpio_num_t red, gpio_num_t yellow, gpio_num_t green);
void      traffic_light_set(traffic_light_t *tl, tl_state_t s);
