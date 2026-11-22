/*
 * บทที่ 3 ตัวอย่าง 5: สาเหตุการรีสตาร์ต
 * ตัวแปร RTC_NOINIT_ATTR อยู่ใน RTC memory ค่าไม่ถูกล้างเมื่อรีสตาร์ตด้วยซอฟต์แวร์
 * (แต่ค่าเป็นขยะเมื่อเพิ่งจ่ายไฟ จึงต้องตรวจด้วย magic number)
 */
#include <stdio.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_attr.h"
#include "esp_log.h"

#define MAGIC 0xC0FFEE42u
static const char *TAG = "restart";

RTC_NOINIT_ATTR static uint32_t s_magic;
RTC_NOINIT_ATTR static uint32_t s_restart_count;

static const char *reason_text(esp_reset_reason_t r)
{
    switch (r) {
    case ESP_RST_POWERON:  return "เปิดเครื่อง (power-on)";
    case ESP_RST_SW:       return "ซอฟต์แวร์สั่ง esp_restart()";
    case ESP_RST_PANIC:    return "โปรแกรม crash (panic)";
    case ESP_RST_INT_WDT:
    case ESP_RST_TASK_WDT:
    case ESP_RST_WDT:      return "watchdog";
    case ESP_RST_BROWNOUT: return "ไฟตก (brownout)";
    case ESP_RST_EXT:      return "กดปุ่ม RST / ขา EN";
    default:               return "อื่นๆ";
    }
}

void app_main(void)
{
    esp_reset_reason_t r = esp_reset_reason();
    if (s_magic != MAGIC || r == ESP_RST_POWERON) {
        s_magic = MAGIC;
        s_restart_count = 0;
    }
    s_restart_count++;
    ESP_LOGI(TAG, "บูตครั้งที่ %" PRIu32 " สาเหตุ: %s (%d)", s_restart_count, reason_text(r), r);

    for (int i = 5; i > 0; i--) {
        ESP_LOGI(TAG, "รีสตาร์ตใน %d วินาที", i);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
    esp_restart();
}
