/*
 * บทที่ 16 ตัวอย่าง 2: rollback
 * เปิด CONFIG_BOOTLOADER_APP_ROLLBACK_ENABLE แล้ว firmware ใหม่บูตครั้งแรกในสถานะ "รอพิสูจน์" (PENDING_VERIFY)
 * ต้องผ่าน self-test แล้วประกาศ "ใช้ได้" ถ้าไม่ประกาศและรีสตาร์ต bootloader จะกลับไปใช้เวอร์ชันเก่า
 * ทดลอง: ตั้ง SIMULATE_BAD_FIRMWARE เป็น 1 ในเวอร์ชันใหม่
 */
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_ota_ops.h"
#include "esp_app_desc.h"
#include "esp_system.h"
#include "esp_log.h"

#define SIMULATE_BAD_FIRMWARE 0
static const char *TAG = "rollback";

static bool self_test(void)
{
    // งานจริง: ตรวจว่าเชื่อมต่อ Wi-Fi/MQTT ได้, อ่านเซนเซอร์ได้, heap พอ ฯลฯ
    vTaskDelay(pdMS_TO_TICKS(2000));
    return !SIMULATE_BAD_FIRMWARE;
}

void app_main(void)
{
    const esp_partition_t *run = esp_ota_get_running_partition();
    esp_ota_img_states_t state;
    ESP_LOGI(TAG, "เวอร์ชัน %s บน %s", esp_app_get_description()->version, run->label);
    if (esp_ota_get_state_partition(run, &state) == ESP_OK && state == ESP_OTA_IMG_PENDING_VERIFY) {
        ESP_LOGW(TAG, "firmware ใหม่ รอพิสูจน์ตัวเอง...");
        if (self_test()) {
            esp_ota_mark_app_valid_cancel_rollback();
            ESP_LOGI(TAG, "self-test ผ่าน ยืนยันใช้เวอร์ชันนี้");
        } else {
            ESP_LOGE(TAG, "self-test ไม่ผ่าน ย้อนกลับเวอร์ชันเดิม");
            esp_ota_mark_app_invalid_rollback_and_reboot();
        }
    } else {
        ESP_LOGI(TAG, "firmware นี้ได้รับการยืนยันแล้ว (state=%d)", state);
    }
}
