/*
 * บทที่ 14 ตัวอย่าง 6: reset log
 * ทุกครั้งที่บูต นับสาเหตุการรีเซ็ตแยกประเภทเก็บใน NVS
 * หลัง 8 วินาที จำลอง task ค้างใน critical section -> interrupt watchdog รีเซ็ตชิป
 */
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs_flash.h"
#include "nvs.h"
#include "esp_system.h"
#include "esp_log.h"

static const char *TAG = "rstlog";
static const char *KEYS[] = { "unknown", "poweron", "ext", "sw", "panic", "int_wdt", "task_wdt", "wdt", "deepsleep", "brownout", "sdio" };

void app_main(void)
{
    ESP_ERROR_CHECK(nvs_flash_init());
    esp_reset_reason_t r = esp_reset_reason();
    const char *key = (r < sizeof(KEYS) / sizeof(KEYS[0])) ? KEYS[r] : "other";
    nvs_handle_t h; uint32_t n = 0;
    ESP_ERROR_CHECK(nvs_open("rstlog", NVS_READWRITE, &h));
    nvs_get_u32(h, key, &n);
    nvs_set_u32(h, key, ++n);
    nvs_commit(h);
    ESP_LOGI(TAG, "สาเหตุครั้งนี้: %s (เกิดมาแล้ว %" PRIu32 " ครั้ง)", key, n);
    for (int i = 0; i < sizeof(KEYS) / sizeof(KEYS[0]); i++) {
        uint32_t v = 0;
        if (nvs_get_u32(h, KEYS[i], &v) == ESP_OK) ESP_LOGI(TAG, "  %-10s %" PRIu32, KEYS[i], v);
    }
    nvs_close(h);

    vTaskDelay(pdMS_TO_TICKS(8000));
    ESP_LOGE(TAG, "จำลองโปรแกรมค้างโดยปิด interrupt (ห้ามทำในงานจริง)");
    portDISABLE_INTERRUPTS();
    while (1) { }                                       // interrupt watchdog จะรีเซ็ตภายในราว 300 ms
}
