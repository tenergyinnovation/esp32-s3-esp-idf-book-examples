/*
 * บทที่ 5 ตัวอย่าง 3: Kconfig ของเราเอง
 * ค่าในเมนู "Greenhouse settings" ถูกแปลงเป็นมาโคร CONFIG_... ตอน build
 */
#include "esp_log.h"
#include "sdkconfig.h"

static const char *TAG = "kconfig";

void app_main(void)
{
    ESP_LOGI(TAG, "ชื่อโรงเรือน: %s", CONFIG_GH_NAME);
    ESP_LOGI(TAG, "เปิดพัดลมเมื่อเกิน: %d C", CONFIG_GH_FAN_ON_TEMP);
#if CONFIG_GH_ENABLE_ALARM
    ESP_LOGI(TAG, "สัญญาณเตือน: เปิด");
#else
    ESP_LOGI(TAG, "สัญญาณเตือน: ปิด");
#endif
}
