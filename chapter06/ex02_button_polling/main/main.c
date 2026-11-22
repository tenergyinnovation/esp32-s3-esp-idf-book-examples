/*
 * บทที่ 6 ตัวอย่าง 2: อ่านปุ่มแบบ polling
 * กดปุ่ม (GPIO5) ค้าง -> LED (GPIO4) ติด ปล่อย -> ดับ
 */
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

#define BTN GPIO_NUM_5
#define LED GPIO_NUM_4

void app_main(void)
{
    gpio_config_t in = { .pin_bit_mask = 1ULL << BTN, .mode = GPIO_MODE_INPUT, .pull_up_en = GPIO_PULLUP_ENABLE };
    gpio_config_t out = { .pin_bit_mask = 1ULL << LED, .mode = GPIO_MODE_OUTPUT };
    ESP_ERROR_CHECK(gpio_config(&in));
    ESP_ERROR_CHECK(gpio_config(&out));

    int last = 1;
    while (1) {
        int level = gpio_get_level(BTN);       // 1 = ไม่กด (pull-up), 0 = กด
        gpio_set_level(LED, level == 0);
        if (level != last) {
            ESP_LOGI("poll", "ปุ่ม %s", level == 0 ? "ถูกกด" : "ถูกปล่อย");
            last = level;
        }
        vTaskDelay(pdMS_TO_TICKS(20));          // ถามทุก 20 ms
    }
}
