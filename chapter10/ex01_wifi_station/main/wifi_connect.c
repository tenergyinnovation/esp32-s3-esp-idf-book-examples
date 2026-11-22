/* wifi_connect.c
 * ลำดับเหตุการณ์: WIFI_EVENT_STA_START -> connect -> IP_EVENT_STA_GOT_IP
 * ถ้าหลุด (WIFI_EVENT_STA_DISCONNECTED) จะรอแบบ exponential backoff: 1, 2, 4, ... สูงสุด 30 วินาที
 */
#include <string.h>
#include "wifi_connect.h"
#include "freertos/event_groups.h"
#include "freertos/timers.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "sdkconfig.h"

#define BIT_CONNECTED BIT0
#define BIT_FAILED    BIT1
static const char *TAG = "wifi";
static EventGroupHandle_t s_eg;
static TimerHandle_t s_retry_timer;
static int s_retry;

static void retry_cb(TimerHandle_t t) { esp_wifi_connect(); }

static void on_event(void *arg, esp_event_base_t base, int32_t id, void *data)
{
    if (base == WIFI_EVENT && id == WIFI_EVENT_STA_START) {
        ESP_LOGI(TAG, "เริ่ม station กำลังเชื่อมต่อ \"%s\"", CONFIG_EX_WIFI_SSID);
        esp_wifi_connect();
    } else if (base == WIFI_EVENT && id == WIFI_EVENT_STA_DISCONNECTED) {
        wifi_event_sta_disconnected_t *d = data;
        xEventGroupClearBits(s_eg, BIT_CONNECTED);
        s_retry++;
        if (CONFIG_EX_WIFI_MAX_RETRY > 0 && s_retry > CONFIG_EX_WIFI_MAX_RETRY) {
            ESP_LOGE(TAG, "เชื่อมต่อไม่สำเร็จ %d ครั้ง ยอมแพ้", CONFIG_EX_WIFI_MAX_RETRY);
            xEventGroupSetBits(s_eg, BIT_FAILED);
            return;
        }
        int wait_s = 1 << (s_retry < 5 ? s_retry - 1 : 5);       /* 1,2,4,8,16,32 */
        if (wait_s > 30) wait_s = 30;
        ESP_LOGW(TAG, "หลุด (reason %d) ลองใหม่ครั้งที่ %d ในอีก %d s", d->reason, s_retry, wait_s);
        xTimerChangePeriod(s_retry_timer, pdMS_TO_TICKS(wait_s * 1000), 0);
        xTimerStart(s_retry_timer, 0);
    } else if (base == IP_EVENT && id == IP_EVENT_STA_GOT_IP) {
        ip_event_got_ip_t *e = data;
        ESP_LOGI(TAG, "ได้ IP: " IPSTR, IP2STR(&e->ip_info.ip));
        s_retry = 0;
        xEventGroupSetBits(s_eg, BIT_CONNECTED);
    }
}

esp_err_t wifi_connect(TickType_t timeout)
{
    esp_err_t err = nvs_flash_init();                       /* Wi-Fi เก็บค่า calibration ใน NVS */
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK(err);
    s_eg = xEventGroupCreate();
    s_retry_timer = xTimerCreate("wifi_retry", pdMS_TO_TICKS(1000), pdFALSE, NULL, retry_cb);
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_sta();
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, on_event, NULL));
    ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, on_event, NULL));
    wifi_config_t wc = { 0 };
    strlcpy((char *)wc.sta.ssid, CONFIG_EX_WIFI_SSID, sizeof(wc.sta.ssid));
    strlcpy((char *)wc.sta.password, CONFIG_EX_WIFI_PASSWORD, sizeof(wc.sta.password));
    wc.sta.threshold.authmode = strlen(CONFIG_EX_WIFI_PASSWORD) ? WIFI_AUTH_WPA2_PSK : WIFI_AUTH_OPEN;
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wc));
    ESP_ERROR_CHECK(esp_wifi_start());
    EventBits_t b = xEventGroupWaitBits(s_eg, BIT_CONNECTED | BIT_FAILED, pdFALSE, pdFALSE, timeout);
    return (b & BIT_CONNECTED) ? ESP_OK : ESP_ERR_TIMEOUT;
}

bool wifi_is_connected(void) { return s_eg && (xEventGroupGetBits(s_eg) & BIT_CONNECTED); }
