/*
 * บทที่ 17 ตัวอย่าง 4: เอฟเฟกต์ RGB LED (WS2812 บนบอร์ด GPIO38)
 * สอนการแปลงสีแบบ HSV -> RGB (หมุนวงล้อสี) และการทำไฟ "หายใจ" ด้วยค่าความสว่างแบบ gamma
 * โหมดเปลี่ยนทุก 5 วินาที: RAINBOW -> BREATHE -> STATUS (กะพริบตามสถานะ)
 */
#include <math.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "led_strip.h"
#include "esp_log.h"

#define RGB_GPIO 38          // บอร์ด v1.0 ใช้ 48
#define MAX_BRIGHT 40        // จำกัดความสว่าง ไม่ให้แสบตาและกินไฟ (WS2812 สว่างเต็มที่ ~60 mA ต่อดวง)
static const char *TAG = "rgb";
static led_strip_handle_t s_strip;

/* HSV: H = ตำแหน่งบนวงล้อสี 0-359 องศา, S = ความสด, V = ความสว่าง */
static void hsv_to_rgb(uint16_t h, uint8_t s, uint8_t v, uint8_t *r, uint8_t *g, uint8_t *b)
{
    uint8_t region = h / 60, rem = (h % 60) * 255 / 60;
    uint8_t p = v * (255 - s) / 255, q = v * (255 - s * rem / 255) / 255, t = v * (255 - s * (255 - rem) / 255) / 255;
    switch (region) {
    case 0: *r = v; *g = t; *b = p; break;
    case 1: *r = q; *g = v; *b = p; break;
    case 2: *r = p; *g = v; *b = t; break;
    case 3: *r = p; *g = q; *b = v; break;
    case 4: *r = t; *g = p; *b = v; break;
    default: *r = v; *g = p; *b = q; break;
    }
}

static void show(uint8_t r, uint8_t g, uint8_t b)
{
    led_strip_set_pixel(s_strip, 0, r, g, b);
    led_strip_refresh(s_strip);
}

void app_main(void)
{
    led_strip_config_t sc = { .strip_gpio_num = RGB_GPIO, .max_leds = 1 };
    led_strip_rmt_config_t rc = { .resolution_hz = 10 * 1000 * 1000 };
    ESP_ERROR_CHECK(led_strip_new_rmt_device(&sc, &rc, &s_strip));

    const char *names[] = { "RAINBOW", "BREATHE", "STATUS" };
    for (int mode = 0; ; mode = (mode + 1) % 3) {
        ESP_LOGI(TAG, "โหมด %s", names[mode]);
        for (int step = 0; step < 250; step++) {                // 250 x 20 ms = 5 s
            uint8_t r, g, b;
            if (mode == 0) {
                hsv_to_rgb((step * 360 / 125) % 360, 255, MAX_BRIGHT, &r, &g, &b);
                show(r, g, b);
            } else if (mode == 1) {
                float x = (1 - cosf(step * 2 * (float)M_PI / 125)) / 2;   // 0..1..0 ทุก 2.5 s
                show(0, 0, (uint8_t)(MAX_BRIGHT * x * x));               // ยกกำลังสอง ≈ gamma ให้ตาเห็นนุ่มนวล
            } else {
                bool on = (step % 50) < 5;                               // กะพริบสั้นๆ ทุก 1 s = "ทำงานปกติ"
                show(0, on ? MAX_BRIGHT : 0, 0);
            }
            vTaskDelay(pdMS_TO_TICKS(20));
        }
    }
}
