/*
 * บทที่ 10 ตัวอย่าง 1: Wi-Fi station
 * โค้ดเชื่อมต่ออยู่ใน wifi_connect.c (ใช้ซ้ำในบทที่ 11 และ 16)
 */
#include "freertos/FreeRTOS.h"
#include "esp_log.h"
#include "esp_wifi.h"
#include "wifi_connect.h"

void app_main(void)
{
    if (wifi_connect(pdMS_TO_TICKS(30000)) != ESP_OK) {
        ESP_LOGE("main", "เชื่อมต่อ Wi-Fi ไม่สำเร็จภายใน 30 วินาที");
        return;
    }
    wifi_ap_record_t ap;
    if (esp_wifi_sta_get_ap_info(&ap) == ESP_OK) {
        ESP_LOGI("main", "เชื่อมต่อ \"%s\" ช่อง %d สัญญาณ %d dBm", (char *)ap.ssid, ap.primary, ap.rssi);
    }
}
