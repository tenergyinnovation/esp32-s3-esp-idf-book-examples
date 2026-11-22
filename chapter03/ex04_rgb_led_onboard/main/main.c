/*
 * บทที่ 3 ตัวอย่าง 4: RGB LED บนบอร์ด DevKitC-1
 * RGB LED เป็นชนิด WS2812 (สั่งด้วยข้อมูลดิจิทัล) ต่อที่ GPIO38 บนบอร์ด v1.1
 * ใช้ component led_strip จาก ESP Component Registry
 */
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "led_strip.h"
#include "esp_log.h"

#define RGB_GPIO   38      // บอร์ด v1.0 ใช้ 48
static const char *TAG = "rgb";

typedef struct { const char *name; uint8_t r, g, b; } color_t;

void app_main(void)
{
    led_strip_config_t strip_cfg = {
        .strip_gpio_num = RGB_GPIO,
        .max_leds = 1,
    };
    led_strip_rmt_config_t rmt_cfg = {
        .resolution_hz = 10 * 1000 * 1000,   // 10 MHz
    };
    led_strip_handle_t strip;
    ESP_ERROR_CHECK(led_strip_new_rmt_device(&strip_cfg, &rmt_cfg, &strip));

    const color_t colors[] = {
        {"แดง", 32, 0, 0}, {"เขียว", 0, 32, 0}, {"น้ำเงิน", 0, 0, 32}, {"ขาว", 20, 20, 20},
    };
    const int n = sizeof(colors) / sizeof(colors[0]);

    for (int i = 0; ; i = (i + 1) % n) {
        ESP_ERROR_CHECK(led_strip_set_pixel(strip, 0, colors[i].r, colors[i].g, colors[i].b));
        ESP_ERROR_CHECK(led_strip_refresh(strip));
        ESP_LOGI(TAG, "สี: %s", colors[i].name);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
