/*
 * บทที่ 10 ตัวอย่าง 2: ทดสอบการต่อใหม่
 * หลังเชื่อมต่อได้ 10 วินาที โปรแกรมจะสั่งตัดการเชื่อมต่อเอง เพื่อดูว่าระบบต่อกลับได้
 * ระยะรอเพิ่มเป็น 1, 2, 4, 8 ... วินาที (ไม่ระดมเชื่อมต่อจน router รำคาญ)
 */
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "wifi_connect.h"

void app_main(void)
{
    ESP_ERROR_CHECK(wifi_connect(portMAX_DELAY));
    for (int round = 1; round <= 3; round++) {
        vTaskDelay(pdMS_TO_TICKS(10000));
        ESP_LOGW("test", "รอบ %d: จำลองสัญญาณหลุด", round);
        esp_wifi_disconnect();                    // ระบบจะได้ event DISCONNECTED แล้วต่อใหม่เอง
        while (!wifi_is_connected()) vTaskDelay(pdMS_TO_TICKS(500));
        ESP_LOGI("test", "รอบ %d: กลับมาออนไลน์แล้ว", round);
    }
}
