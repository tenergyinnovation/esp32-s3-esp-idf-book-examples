/*
 * บทที่ 3 ตัวอย่าง 2: อ่านข้อมูลชิป
 * ใช้ esp_chip_info(), esp_flash_get_size() และ esp_psram_get_size()
 */
#include <stdio.h>
#include <inttypes.h>
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_psram.h"
#include "esp_system.h"
#include "esp_log.h"

static const char *TAG = "chip_info";

void app_main(void)
{
    esp_chip_info_t info;
    esp_chip_info(&info);

    ESP_LOGI(TAG, "ชิป: %s", CONFIG_IDF_TARGET);
    ESP_LOGI(TAG, "จำนวน core: %d", info.cores);
    ESP_LOGI(TAG, "revision: v%d.%d", info.revision / 100, info.revision % 100);
    ESP_LOGI(TAG, "Wi-Fi: %s, BLE: %s",
             (info.features & CHIP_FEATURE_WIFI_BGN) ? "มี" : "ไม่มี",
             (info.features & CHIP_FEATURE_BLE) ? "มี" : "ไม่มี");

    uint32_t flash_size = 0;
    if (esp_flash_get_size(NULL, &flash_size) == ESP_OK) {
        ESP_LOGI(TAG, "Flash: %" PRIu32 " MB", flash_size / (1024 * 1024));
    }

    if (esp_psram_is_initialized()) {
        ESP_LOGI(TAG, "PSRAM: %u MB", (unsigned)(esp_psram_get_size() / (1024 * 1024)));
    } else {
        ESP_LOGW(TAG, "ไม่พบ PSRAM (ปกติเมื่อรันบน Wokwi หรือ QEMU)");
    }
    ESP_LOGI(TAG, "heap ว่าง: %" PRIu32 " bytes", esp_get_free_heap_size());
}
