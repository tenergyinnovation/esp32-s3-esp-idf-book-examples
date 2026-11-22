/*
 * บทที่ 11 ตัวอย่าง 3: MQTT publish / subscribe
 * broker สาธารณะสำหรับทดสอบ: mqtt://broker.emqx.io:1883
 * subscribe หัวข้อ tenergy/book/<MAC>/cmd   publish หัวข้อ tenergy/book/<MAC>/temp ทุก 5 วินาที
 * ทดลองสั่งจากคอมพิวเตอร์: mosquitto_pub -h broker.emqx.io -t tenergy/book/<MAC>/cmd -m "hello"
 */
#include <stdio.h>
#include "mqtt_client.h"
#include "esp_mac.h"
#include "esp_random.h"
#include "esp_log.h"
#include "wifi_connect.h"

static const char *TAG = "mqtt";
static char s_base[48];

static void on_mqtt(void *arg, esp_event_base_t base, int32_t id, void *data)
{
    esp_mqtt_event_handle_t e = data;
    char topic[64];
    switch ((esp_mqtt_event_id_t)id) {
    case MQTT_EVENT_CONNECTED:
        ESP_LOGI(TAG, "เชื่อมต่อ broker แล้ว");
        snprintf(topic, sizeof topic, "%s/cmd", s_base);
        esp_mqtt_client_subscribe(e->client, topic, 1);
        ESP_LOGI(TAG, "subscribe %s", topic);
        break;
    case MQTT_EVENT_DISCONNECTED: ESP_LOGW(TAG, "หลุดจาก broker (client จะต่อใหม่เอง)"); break;
    case MQTT_EVENT_DATA:
        ESP_LOGI(TAG, "ได้ข้อความ [%.*s] = %.*s", e->topic_len, e->topic, e->data_len, e->data);
        break;
    default: break;
    }
}

void app_main(void)
{
    ESP_ERROR_CHECK(wifi_connect(portMAX_DELAY));
    uint8_t mac[6]; esp_read_mac(mac, ESP_MAC_WIFI_STA);
    snprintf(s_base, sizeof s_base, "tenergy/book/%02x%02x%02x", mac[3], mac[4], mac[5]);

    esp_mqtt_client_config_t cfg = { .broker.address.uri = "mqtt://broker.emqx.io:1883" };
    esp_mqtt_client_handle_t client = esp_mqtt_client_init(&cfg);
    esp_mqtt_client_register_event(client, ESP_EVENT_ANY_ID, on_mqtt, NULL);
    ESP_ERROR_CHECK(esp_mqtt_client_start(client));

    char topic[64], msg[32];
    snprintf(topic, sizeof topic, "%s/temp", s_base);
    while (1) {
        vTaskDelay(pdMS_TO_TICKS(5000));
        snprintf(msg, sizeof msg, "%.1f", 25.0f + (esp_random() % 100) / 10.0f);
        int id = esp_mqtt_client_publish(client, topic, msg, 0, 1, 0);   // QoS 1, ไม่ retain
        ESP_LOGI(TAG, "publish %s = %s (msg_id=%d)", topic, msg, id);
    }
}
