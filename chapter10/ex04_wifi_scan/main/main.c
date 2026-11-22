/*
 * บทที่ 10 ตัวอย่าง 4: สแกน Wi-Fi
 * แสดงชื่อ ความแรงสัญญาณ (RSSI) ช่อง และชนิดการเข้ารหัส
 */
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "esp_log.h"
#include "nvs_flash.h"

#define MAX_AP 20

static const char *auth_name(wifi_auth_mode_t m)
{
    switch (m) {
    case WIFI_AUTH_OPEN: return "OPEN";
    case WIFI_AUTH_WPA2_PSK: return "WPA2";
    case WIFI_AUTH_WPA_WPA2_PSK: return "WPA/WPA2";
    case WIFI_AUTH_WPA3_PSK: return "WPA3";
    case WIFI_AUTH_WPA2_WPA3_PSK: return "WPA2/WPA3";
    default: return "อื่นๆ";
    }
}

void app_main(void)
{
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_sta();
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_start());

    ESP_ERROR_CHECK(esp_wifi_scan_start(NULL, true));      // true = รอจนสแกนเสร็จ
    uint16_t n = MAX_AP;
    static wifi_ap_record_t aps[MAX_AP];
    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_records(&n, aps));
    ESP_LOGI("scan", "พบ %u เครือข่าย", n);
    for (int i = 0; i < n; i++) {
        const char *bar = aps[i].rssi > -55 ? "████" : aps[i].rssi > -67 ? "███ " : aps[i].rssi > -75 ? "██  " : "█   ";
        ESP_LOGI("scan", "%2d. %-24s %4d dBm %s ch%2d %s", i + 1, (char *)aps[i].ssid, aps[i].rssi, bar,
                 aps[i].primary, auth_name(aps[i].authmode));
    }
}
