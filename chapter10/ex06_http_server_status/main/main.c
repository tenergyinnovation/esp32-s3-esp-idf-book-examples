/*
 * บทที่ 10 ตัวอย่าง 6: HTTP server
 * เปิดเบราว์เซอร์ไปที่ http://<IP บอร์ด>/ เพื่อดูสถานะ
 * GET /api/status ส่งข้อมูลเป็น JSON
 */
#include <stdio.h>
#include <inttypes.h>
#include "esp_http_server.h"
#include "esp_timer.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "wifi_connect.h"

static esp_err_t root_get(httpd_req_t *req)
{
    static const char html[] =
        "<!doctype html><meta charset=utf-8><meta name=viewport content='width=device-width'>"
        "<title>ESP32-S3</title><h2>สถานะบอร์ด ESP32-S3</h2><pre id=s>กำลังโหลด...</pre>"
        "<script>setInterval(async()=>{s.textContent=JSON.stringify(await(await fetch('/api/status')).json(),null,2)},1000)</script>";
    httpd_resp_set_type(req, "text/html");
    return httpd_resp_send(req, html, HTTPD_RESP_USE_STRLEN);
}

static esp_err_t status_get(httpd_req_t *req)
{
    wifi_ap_record_t ap = { 0 };
    esp_wifi_sta_get_ap_info(&ap);
    char json[160];
    snprintf(json, sizeof json, "{\"uptime_s\":%lld,\"free_heap\":%" PRIu32 ",\"rssi\":%d}",
             esp_timer_get_time() / 1000000, esp_get_free_heap_size(), ap.rssi);
    httpd_resp_set_type(req, "application/json");
    return httpd_resp_send(req, json, HTTPD_RESP_USE_STRLEN);
}

void app_main(void)
{
    ESP_ERROR_CHECK(wifi_connect(portMAX_DELAY));
    httpd_handle_t server;
    httpd_config_t cfg = HTTPD_DEFAULT_CONFIG();
    ESP_ERROR_CHECK(httpd_start(&server, &cfg));
    httpd_uri_t root = { .uri = "/", .method = HTTP_GET, .handler = root_get };
    httpd_uri_t api  = { .uri = "/api/status", .method = HTTP_GET, .handler = status_get };
    httpd_register_uri_handler(server, &root);
    httpd_register_uri_handler(server, &api);
    ESP_LOGI("web", "เว็บเซิร์ฟเวอร์พร้อมที่พอร์ต %d", cfg.server_port);
}
