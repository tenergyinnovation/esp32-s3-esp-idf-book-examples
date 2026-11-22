/*
 * บทที่ 11 ตัวอย่าง 2: HTTPS
 * esp_crt_bundle_attach = ใช้ "สมุดรายชื่อ CA ที่เชื่อถือได้" ที่มากับ ESP-IDF ตรวจใบรับรองของเว็บ
 */
#include "esp_http_client.h"
#include "esp_crt_bundle.h"
#include "esp_log.h"
#include "wifi_connect.h"

static const char *TAG = "https";

static esp_err_t on_http(esp_http_client_event_t *e)
{
    if (e->event_id == HTTP_EVENT_ON_DATA) ESP_LOGI(TAG, "ได้ข้อมูล %d bytes", e->data_len);
    return ESP_OK;
}

void app_main(void)
{
    ESP_ERROR_CHECK(wifi_connect(portMAX_DELAY));
    esp_http_client_config_t cfg = {
        .url = "https://www.howsmyssl.com/a/check",
        .crt_bundle_attach = esp_crt_bundle_attach,
        .event_handler = on_http,
        .timeout_ms = 15000,
    };
    esp_http_client_handle_t c = esp_http_client_init(&cfg);
    esp_err_t err = esp_http_client_perform(c);              // ทำครบ: เชื่อมต่อ TLS ส่ง GET รับข้อมูล
    if (err == ESP_OK) ESP_LOGI(TAG, "สำเร็จ status=%d (การเชื่อมต่อถูกเข้ารหัส)", esp_http_client_get_status_code(c));
    else ESP_LOGE(TAG, "ล้มเหลว: %s", esp_err_to_name(err));
    esp_http_client_cleanup(c);
}
