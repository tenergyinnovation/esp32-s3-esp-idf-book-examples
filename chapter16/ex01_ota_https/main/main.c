/*
 * บทที่ 16 ตัวอย่าง 1: OTA ผ่าน HTTPS
 * ดาวน์โหลด firmware ใหม่ลงช่องที่ "ว่าง" (ota_0 หรือ ota_1) ระหว่างโปรแกรมเดิมยังทำงาน
 * ดาวน์โหลดครบและตรวจสอบผ่าน -> สลับช่องบูตแล้วรีสตาร์ต
 */
#include "esp_https_ota.h"
#include "esp_ota_ops.h"
#include "esp_crt_bundle.h"
#include "esp_app_desc.h"
#include "esp_system.h"
#include "esp_log.h"
#include "wifi_connect.h"

static const char *TAG = "ota";

void app_main(void)
{
    const esp_partition_t *run = esp_ota_get_running_partition();
    ESP_LOGI(TAG, "เวอร์ชันปัจจุบัน %s รันจาก %s", esp_app_get_description()->version, run->label);
    ESP_ERROR_CHECK(wifi_connect(portMAX_DELAY));

    esp_http_client_config_t http = {
        .url = CONFIG_EX_OTA_URL,
        .crt_bundle_attach = esp_crt_bundle_attach,     // server ทดสอบในเครื่องที่ใช้ self-signed ให้ใช้ .cert_pem แทน
        .timeout_ms = 15000,
        .keep_alive_enable = true,
    };
    esp_https_ota_config_t cfg = { .http_config = &http };
    ESP_LOGI(TAG, "เริ่มดาวน์โหลดจาก %s", CONFIG_EX_OTA_URL);
    esp_err_t err = esp_https_ota(&cfg);
    if (err == ESP_OK) {
        ESP_LOGI(TAG, "อัปเดตสำเร็จ จะบูตจาก %s หลังรีสตาร์ต", esp_ota_get_next_update_partition(NULL)->label);
        esp_restart();
    }
    ESP_LOGE(TAG, "อัปเดตไม่สำเร็จ (%s) ยังใช้เวอร์ชันเดิมต่อ", esp_err_to_name(err));
}
