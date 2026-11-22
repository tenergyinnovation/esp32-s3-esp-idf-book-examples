/*
 * บทที่ 4 ตัวอย่าง 6: ระบบ Logging
 * E=Error W=Warning I=Info D=Debug V=Verbose
 */
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

static const char *TAG_SENSOR = "sensor";
static const char *TAG_WIFI   = "wifi_app";

static void print_all(void)
{
    ESP_LOGE(TAG_SENSOR, "เซนเซอร์ไม่ตอบ (Error)");
    ESP_LOGW(TAG_SENSOR, "อุณหภูมิสูงผิดปกติ (Warning)");
    ESP_LOGI(TAG_SENSOR, "อ่านค่า 28.5 C (Info)");
    ESP_LOGD(TAG_SENSOR, "raw=0x6F2A (Debug)");
    ESP_LOGV(TAG_SENSOR, "รายละเอียดทุก byte (Verbose)");
    ESP_LOGI(TAG_WIFI,   "เชื่อมต่อแล้ว (Info)");
}

void app_main(void)
{
    ESP_LOGI("main", "--- ค่าเริ่มต้น (แสดงถึงระดับ Info) ---");
    print_all();

    ESP_LOGI("main", "--- เปิด Debug เฉพาะ tag sensor ---");
    esp_log_level_set(TAG_SENSOR, ESP_LOG_DEBUG);
    print_all();

    ESP_LOGI("main", "--- ปิด log ของ wifi_app ยกเว้น Error ---");
    esp_log_level_set(TAG_WIFI, ESP_LOG_ERROR);
    print_all();
}
