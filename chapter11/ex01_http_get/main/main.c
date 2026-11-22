/*
 * บทที่ 11 ตัวอย่าง 1: HTTP client
 * ขอหน้าเว็บ http://example.com แล้วแสดงรหัสตอบกลับ ขนาด และ 120 ตัวอักษรแรก
 */
#include <string.h>
#include "esp_http_client.h"
#include "esp_log.h"
#include "wifi_connect.h"

static const char *TAG = "http";

void app_main(void)
{
    ESP_ERROR_CHECK(wifi_connect(portMAX_DELAY));
    esp_http_client_config_t cfg = { .url = "http://example.com/", .timeout_ms = 10000 };
    esp_http_client_handle_t c = esp_http_client_init(&cfg);

    ESP_ERROR_CHECK(esp_http_client_open(c, 0));                 // 0 = ไม่มี body ส่งไป (GET)
    int64_t len = esp_http_client_fetch_headers(c);
    int status = esp_http_client_get_status_code(c);
    char body[121] = { 0 };
    int n = esp_http_client_read(c, body, sizeof(body) - 1);
    ESP_LOGI(TAG, "status=%d  content-length=%lld", status, len);
    ESP_LOGI(TAG, "อ่านได้ %d bytes แรก: %s", n, body);
    esp_http_client_cleanup(c);
}
