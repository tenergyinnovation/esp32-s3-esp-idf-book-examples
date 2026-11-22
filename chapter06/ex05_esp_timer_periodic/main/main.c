/*
 * บทที่ 6 ตัวอย่าง 5: esp_timer
 * timer แบบ periodic (ทุก 500 ms) และ one-shot (ครั้งเดียวหลัง 3 s)
 */
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_timer.h"
#include "esp_log.h"

#define LED GPIO_NUM_4
static const char *TAG = "timer";

static void blink_cb(void *arg)
{
    static int on = 0;
    on = !on;
    gpio_set_level(LED, on);
}

static void once_cb(void *arg)
{
    ESP_LOGI(TAG, "one-shot ทำงานที่ %" PRId64 " ms", esp_timer_get_time() / 1000);
}

void app_main(void)
{
    gpio_config_t out = { .pin_bit_mask = 1ULL << LED, .mode = GPIO_MODE_OUTPUT };
    ESP_ERROR_CHECK(gpio_config(&out));

    esp_timer_handle_t blink, once;
    const esp_timer_create_args_t a1 = { .callback = blink_cb, .name = "blink" };
    const esp_timer_create_args_t a2 = { .callback = once_cb,  .name = "once" };
    ESP_ERROR_CHECK(esp_timer_create(&a1, &blink));
    ESP_ERROR_CHECK(esp_timer_create(&a2, &once));
    ESP_ERROR_CHECK(esp_timer_start_periodic(blink, 500 * 1000));   // หน่วยเป็น microsecond
    ESP_ERROR_CHECK(esp_timer_start_once(once, 3 * 1000 * 1000));
    ESP_LOGI(TAG, "เริ่ม timer ที่ %" PRId64 " ms (app_main จบได้ timer ยังทำงานต่อ)", esp_timer_get_time() / 1000);
}
