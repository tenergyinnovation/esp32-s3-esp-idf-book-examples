/*
 * บทที่ 5 ตัวอย่าง 5: managed component
 * ไฟล์ main/idf_component.yml ระบุ dependency "espressif/led_strip"
 * ตอน build ESP-IDF จะดาวน์โหลดมาไว้ในโฟลเดอร์ managed_components/ เอง
 * ตัวอย่างนี้ทำไฟวิ่งสีรุ้งบน RGB LED (GPIO38)
 */
#include <math.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "led_strip.h"

static void hsv_to_rgb(float h, uint8_t *r, uint8_t *g, uint8_t *b)
{
    // แปลงเฉดสี (0-360 องศา) เป็น RGB แบบง่าย ความสว่างต่ำ
    float x = 1.0f - fabsf(fmodf(h / 60.0f, 2.0f) - 1.0f);
    float rf = 0, gf = 0, bf = 0;
    if (h < 60)       { rf = 1; gf = x; }
    else if (h < 120) { rf = x; gf = 1; }
    else if (h < 180) { gf = 1; bf = x; }
    else if (h < 240) { gf = x; bf = 1; }
    else if (h < 300) { rf = x; bf = 1; }
    else              { rf = 1; bf = x; }
    *r = rf * 40; *g = gf * 40; *b = bf * 40;
}

void app_main(void)
{
    led_strip_config_t cfg = { .strip_gpio_num = 38, .max_leds = 1 };
    led_strip_rmt_config_t rmt = { .resolution_hz = 10000000 };
    led_strip_handle_t strip;
    ESP_ERROR_CHECK(led_strip_new_rmt_device(&cfg, &rmt, &strip));

    for (float h = 0; ; h = fmodf(h + 5, 360)) {
        uint8_t r, g, b;
        hsv_to_rgb(h, &r, &g, &b);
        led_strip_set_pixel(strip, 0, r, g, b);
        led_strip_refresh(strip);
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}
