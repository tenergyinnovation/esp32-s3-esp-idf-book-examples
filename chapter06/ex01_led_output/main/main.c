/*
 * บทที่ 6 ตัวอย่าง 1: GPIO output หลายขา
 * ตั้งค่าครั้งเดียวด้วย gpio_config() แล้วทำไฟวิ่ง 4 ดวง
 */
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

static const gpio_num_t LEDS[] = { GPIO_NUM_4, GPIO_NUM_5, GPIO_NUM_6, GPIO_NUM_7 };
#define N_LEDS (sizeof(LEDS) / sizeof(LEDS[0]))

void app_main(void)
{
    uint64_t mask = 0;
    for (int i = 0; i < N_LEDS; i++) mask |= 1ULL << LEDS[i];   // รวมทุกขาเป็น bit mask
    gpio_config_t cfg = { .pin_bit_mask = mask, .mode = GPIO_MODE_OUTPUT };
    ESP_ERROR_CHECK(gpio_config(&cfg));

    for (int step = 0; ; step = (step + 1) % N_LEDS) {
        for (int i = 0; i < N_LEDS; i++) gpio_set_level(LEDS[i], i == step);
        ESP_LOGI("leds", "ดวงที่ %d ติด", step + 1);
        vTaskDelay(pdMS_TO_TICKS(250));
    }
}
