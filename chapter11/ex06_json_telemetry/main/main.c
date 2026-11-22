/*
 * บทที่ 11 ตัวอย่าง 6: JSON telemetry
 * สร้าง JSON ด้วย snprintf (ไม่ต้องพึ่งไลบรารีเพิ่ม) แล้ว publish ทุก 10 วินาที
 * ตัวอย่าง: {"device":"gh-a1b2c3","seq":7,"temp":28.4,"hum":61.0,"fan":false,"uptime":70}
 */
#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>
#include "mqtt_client.h"
#include "esp_mac.h"
#include "esp_timer.h"
#include "esp_random.h"
#include "esp_log.h"
#include "wifi_connect.h"

typedef struct { float temp, hum; bool fan; } sample_t;

static int to_json(char *out, size_t n, const char *dev, uint32_t seq, const sample_t *s)
{
    return snprintf(out, n, "{\"device\":\"%s\",\"seq\":%" PRIu32 ",\"temp\":%.1f,\"hum\":%.1f,\"fan\":%s,\"uptime\":%lld}",
                    dev, seq, s->temp, s->hum, s->fan ? "true" : "false", esp_timer_get_time() / 1000000);
}

void app_main(void)
{
    ESP_ERROR_CHECK(wifi_connect(portMAX_DELAY));
    uint8_t mac[6]; esp_read_mac(mac, ESP_MAC_WIFI_STA);
    char dev[16], topic[64];
    snprintf(dev, sizeof dev, "gh-%02x%02x%02x", mac[3], mac[4], mac[5]);
    snprintf(topic, sizeof topic, "tenergy/book/%s/telemetry", dev);

    esp_mqtt_client_config_t cfg = { .broker.address.uri = "mqtt://broker.emqx.io:1883" };
    esp_mqtt_client_handle_t c = esp_mqtt_client_init(&cfg);
    ESP_ERROR_CHECK(esp_mqtt_client_start(c));

    for (uint32_t seq = 1; ; seq++) {
        sample_t s = { .temp = 25 + (esp_random() % 100) / 10.0f, .hum = 55 + (esp_random() % 150) / 10.0f };
        s.fan = s.temp > 32;
        char json[192];
        int len = to_json(json, sizeof json, dev, seq, &s);
        if (len >= sizeof json) { ESP_LOGE("json", "buffer เล็กไป"); continue; }
        esp_mqtt_client_publish(c, topic, json, len, 1, 0);
        ESP_LOGI("json", "%s", json);
        vTaskDelay(pdMS_TO_TICKS(10000));
    }
}
