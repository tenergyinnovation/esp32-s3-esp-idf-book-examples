/*
 * บทที่ 12 ตัวอย่าง 5: Wi-Fi provisioning ผ่าน BLE
 * ครั้งแรก: บอร์ดยังไม่รู้จัก Wi-Fi -> เปิด BLE ชื่อ PROV_xxxxxx ให้แอป "ESP BLE Provisioning" ส่งชื่อ/รหัส Wi-Fi มา
 * ครั้งต่อไป: ข้อมูล Wi-Fi ถูกเก็บใน NVS แล้ว จึงเชื่อมต่อเลย
 * กดปุ่ม BOOT ค้างตอนเปิดเครื่องเพื่อล้างค่า (ทำในบทที่ 13)
 */
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "esp_mac.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "network_provisioning/manager.h"
#include "network_provisioning/scheme_ble.h"

static const char *TAG = "prov";
static EventGroupHandle_t s_eg;

static void on_event(void *arg, esp_event_base_t base, int32_t id, void *data)
{
    if (base == NETWORK_PROV_EVENT) {
        if (id == NETWORK_PROV_START) ESP_LOGI(TAG, "เริ่ม provisioning รอแอปมือถือ");
        else if (id == NETWORK_PROV_WIFI_CRED_RECV) {
            wifi_sta_config_t *c = data;
            ESP_LOGI(TAG, "ได้รับ Wi-Fi \"%s\" จากมือถือ", (const char *)c->ssid);
        } else if (id == NETWORK_PROV_WIFI_CRED_FAIL) ESP_LOGE(TAG, "เชื่อมต่อไม่ได้ ตรวจรหัสผ่าน");
        else if (id == NETWORK_PROV_WIFI_CRED_SUCCESS) ESP_LOGI(TAG, "ตั้งค่า Wi-Fi สำเร็จ");
        else if (id == NETWORK_PROV_END) network_prov_mgr_deinit();
    } else if (base == WIFI_EVENT && id == WIFI_EVENT_STA_START) {
        esp_wifi_connect();
    } else if (base == WIFI_EVENT && id == WIFI_EVENT_STA_DISCONNECTED) {
        esp_wifi_connect();
    } else if (base == IP_EVENT && id == IP_EVENT_STA_GOT_IP) {
        ip_event_got_ip_t *e = data;
        ESP_LOGI(TAG, "ออนไลน์แล้ว IP " IPSTR, IP2STR(&e->ip_info.ip));
        xEventGroupSetBits(s_eg, BIT0);
    }
}

void app_main(void)
{
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) { nvs_flash_erase(); err = nvs_flash_init(); }
    ESP_ERROR_CHECK(err);
    s_eg = xEventGroupCreate();
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    ESP_ERROR_CHECK(esp_event_handler_register(NETWORK_PROV_EVENT, ESP_EVENT_ANY_ID, on_event, NULL));
    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, on_event, NULL));
    ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, on_event, NULL));
    esp_netif_create_default_wifi_sta();
    wifi_init_config_t wcfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&wcfg));

    network_prov_mgr_config_t cfg = {
        .scheme = network_prov_scheme_ble,
        .scheme_event_handler = NETWORK_PROV_SCHEME_BLE_EVENT_HANDLER_FREE_BTDM,
    };
    ESP_ERROR_CHECK(network_prov_mgr_init(cfg));
    bool provisioned = false;
    ESP_ERROR_CHECK(network_prov_mgr_is_wifi_provisioned(&provisioned));

    if (!provisioned) {
        uint8_t mac[6]; esp_read_mac(mac, ESP_MAC_WIFI_STA);
        char name[16]; snprintf(name, sizeof name, "PROV_%02X%02X%02X", mac[3], mac[4], mac[5]);
        const char *pop = "tenergy1";               /* proof-of-possession: รหัสที่ติดบนกล่องสินค้า */
        ESP_LOGI(TAG, "ยังไม่มี Wi-Fi เปิดแอปแล้วเลือก %s รหัส PoP: %s", name, pop);
        ESP_ERROR_CHECK(network_prov_mgr_start_provisioning(NETWORK_PROV_SECURITY_1, pop, name, NULL));
    } else {
        ESP_LOGI(TAG, "มีข้อมูล Wi-Fi แล้ว เชื่อมต่อเลย");
        network_prov_mgr_deinit();
        ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
        ESP_ERROR_CHECK(esp_wifi_start());
    }
    xEventGroupWaitBits(s_eg, BIT0, pdFALSE, pdTRUE, portMAX_DELAY);
    ESP_LOGI(TAG, "พร้อมทำงานหลักของอุปกรณ์");
}
