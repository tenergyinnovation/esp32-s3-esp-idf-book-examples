/*
 * บทที่ 5 ตัวอย่าง 4: ตรวจว่า sdkconfig.defaults ทำงาน
 * ไฟล์ sdkconfig.defaults ตั้ง Flash 16 MB, PSRAM octal และ CPU 240 MHz
 */
#include <inttypes.h>
#include "esp_flash.h"
#include "esp_psram.h"
#include "esp_log.h"
#include "sdkconfig.h"

static const char *TAG = "defaults";

void app_main(void)
{
    uint32_t size = 0;
    esp_flash_get_size(NULL, &size);
    ESP_LOGI(TAG, "CPU: %d MHz", CONFIG_ESP_DEFAULT_CPU_FREQ_MHZ);
    ESP_LOGI(TAG, "Flash ตาม sdkconfig: %s / ตรวจจริง: %" PRIu32 " MB", CONFIG_ESPTOOLPY_FLASHSIZE, size >> 20);
#if CONFIG_SPIRAM
    ESP_LOGI(TAG, "PSRAM เปิดใช้: %s, ขนาด %u MB", esp_psram_is_initialized() ? "พบ" : "ไม่พบ",
             (unsigned)(esp_psram_get_size() >> 20));
#endif
}
