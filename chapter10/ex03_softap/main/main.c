/*
 * บทที่ 10 ตัวอย่าง 3: SoftAP
 * บอร์ดปล่อย Wi-Fi ชื่อ "Greenhouse-Setup" ใช้ตอนตั้งค่าอุปกรณ์ครั้งแรก
 * มือถือที่เข้ามาจะได้ IP ในวง 192.168.4.x
 */
#include <string.h>
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_mac.h"

static const char *TAG = "softap";

static void on_event(void *arg, esp_event_base_t base, int32_t id, void *data)
{
    if (id == WIFI_EVENT_AP_STACONNECTED) {
        wifi_event_ap_staconnected_t *e = data;
        ESP_LOGI(TAG, "มีอุปกรณ์เข้ามา MAC " MACSTR, MAC2STR(e->mac));
    } else if (id == WIFI_EVENT_AP_STADISCONNECTED) {
        ESP_LOGI(TAG, "อุปกรณ์ออกไปแล้ว");
    }
}

void app_main(void)
{
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_ap();
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, on_event, NULL));

    wifi_config_t ap = {
        .ap = { .ssid = "Greenhouse-Setup", .password = "tenergy123", .channel = 6,
                .max_connection = 4, .authmode = WIFI_AUTH_WPA2_PSK },
    };
    ap.ap.ssid_len = strlen((char *)ap.ap.ssid);
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &ap));
    ESP_ERROR_CHECK(esp_wifi_start());
    ESP_LOGI(TAG, "เปิด Wi-Fi \"%s\" รหัส \"%s\" แล้ว", ap.ap.ssid, ap.ap.password);
}
