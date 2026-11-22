/*
 * บทที่ 4 ตัวอย่าง 4: volatile
 * ISR (ฮาร์ดแวร์เรียกเอง) เขียน flag ส่วน app_main อ่าน flag
 * ปุ่มต่อ GPIO5 ลง GND ใช้ pull-up ภายใน (ไม่กด = 1, กด = 0)
 */
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_attr.h"
#include "esp_log.h"

#define BUTTON_GPIO GPIO_NUM_5
static const char *TAG = "volatile";

static volatile bool     s_pressed = false;   // ISR เขียน, task อ่าน
static volatile uint32_t s_isr_count = 0;     // เขียนฝั่งเดียว (ISR) จึงปลอดภัย

static void IRAM_ATTR button_isr(void *arg)
{
    s_isr_count++;
    s_pressed = true;          // ทำงานสั้นที่สุด แค่ "แปะโน้ต"
}

void app_main(void)
{
    const gpio_config_t cfg = {
        .pin_bit_mask = 1ULL << BUTTON_GPIO,
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .intr_type = GPIO_INTR_NEGEDGE,       // ขอบขาลง = เพิ่งกด
    };
    ESP_ERROR_CHECK(gpio_config(&cfg));
    ESP_ERROR_CHECK(gpio_install_isr_service(0));
    ESP_ERROR_CHECK(gpio_isr_handler_add(BUTTON_GPIO, button_isr, NULL));
    ESP_LOGI(TAG, "พร้อม กดปุ่มที่ GPIO5");

    while (1) {
        if (s_pressed) {
            s_pressed = false;
            ESP_LOGI(TAG, "มีการกดปุ่ม (ISR ทำงานรวม %" PRIu32 " ครั้ง)", s_isr_count);
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
