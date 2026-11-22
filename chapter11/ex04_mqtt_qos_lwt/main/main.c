/*
 * บทที่ 11 ตัวอย่าง 4: LWT (Last Will and Testament)
 * ตอนเชื่อมต่อ เราฝาก broker ไว้ว่า "ถ้าฉันหายไปเฉยๆ ให้ประกาศ status = offline"
 * เมื่อต่อได้ publish status = online แบบ retained (ใครมา subscribe ทีหลังก็เห็นค่าล่าสุดทันที)
 */
#include <stdio.h>
#include "mqtt_client.h"
#include "esp_log.h"
#include "wifi_connect.h"

#define STATUS_TOPIC "tenergy/book/greenhouse-a/status"
static const char *TAG = "lwt";

static void on_mqtt(void *arg, esp_event_base_t base, int32_t id, void *data)
{
    esp_mqtt_event_handle_t e = data;
    if (id == MQTT_EVENT_CONNECTED) {
        esp_mqtt_client_publish(e->client, STATUS_TOPIC, "online", 0, 1, 1);   // QoS1 + retain
        ESP_LOGI(TAG, "ประกาศ online (retained)");
    } else if (id == MQTT_EVENT_PUBLISHED) {
        ESP_LOGI(TAG, "broker ยืนยันได้รับ msg_id=%d (QoS 1)", e->msg_id);
    }
}

void app_main(void)
{
    ESP_ERROR_CHECK(wifi_connect(portMAX_DELAY));
    esp_mqtt_client_config_t cfg = {
        .broker.address.uri = "mqtt://broker.emqx.io:1883",
        .session.keepalive = 15,                          // ถ้าเงียบเกิน ~1.5 เท่าของ 15 s broker ถือว่าหาย
        .session.last_will = { .topic = STATUS_TOPIC, .msg = "offline", .qos = 1, .retain = 1 },
    };
    esp_mqtt_client_handle_t c = esp_mqtt_client_init(&cfg);
    esp_mqtt_client_register_event(c, ESP_EVENT_ANY_ID, on_mqtt, NULL);
    ESP_ERROR_CHECK(esp_mqtt_client_start(c));
}
