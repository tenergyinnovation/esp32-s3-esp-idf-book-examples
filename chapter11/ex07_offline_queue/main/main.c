/*
 * บทที่ 11 ตัวอย่าง 7: store-and-forward
 * วัดค่าทุก 2 วินาทีเสมอ ถ้า MQTT ยังไม่เชื่อมต่อ เก็บไว้ใน ring buffer (สูงสุด 32 ค่า)
 * เมื่อเชื่อมต่อได้ ทยอยส่งของค้างก่อน (เหมือนบุรุษไปรษณีย์ที่เก็บจดหมายไว้ส่งเมื่อถนนเปิด)
 */
#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>
#include "mqtt_client.h"
#include "esp_timer.h"
#include "esp_random.h"
#include "esp_log.h"
#include "wifi_connect.h"

#define QCAP 32
typedef struct { uint32_t seq; int64_t t_ms; float temp; } rec_t;
static rec_t s_q[QCAP];
static int s_head, s_count;
static volatile bool s_online;
static const char *TAG = "sf";

static void q_push(rec_t r)
{
    if (s_count == QCAP) { s_head = (s_head + 1) % QCAP; s_count--; ESP_LOGW(TAG, "คิวเต็ม ทิ้งค่าเก่าสุด"); }
    s_q[(s_head + s_count) % QCAP] = r; s_count++;
}

static void on_mqtt(void *a, esp_event_base_t b, int32_t id, void *d)
{
    if (id == MQTT_EVENT_CONNECTED) { s_online = true;  ESP_LOGI(TAG, "ออนไลน์ มีของค้าง %d ค่า", s_count); }
    if (id == MQTT_EVENT_DISCONNECTED) { s_online = false; ESP_LOGW(TAG, "ออฟไลน์ เริ่มเก็บค่าไว้ก่อน"); }
}

void app_main(void)
{
    esp_mqtt_client_handle_t c = NULL;
    bool started = false;
    for (uint32_t seq = 1; ; seq++) {
        q_push((rec_t){ .seq = seq, .t_ms = esp_timer_get_time() / 1000, .temp = 25 + (esp_random() % 80) / 10.0f });
        if (!started && seq == 5) {      // จำลอง: เน็ตเพิ่งพร้อมหลังวัดไปแล้ว 5 ค่า
            ESP_ERROR_CHECK(wifi_connect(portMAX_DELAY));
            esp_mqtt_client_config_t cfg = { .broker.address.uri = "mqtt://broker.emqx.io:1883" };
            c = esp_mqtt_client_init(&cfg);
            esp_mqtt_client_register_event(c, ESP_EVENT_ANY_ID, on_mqtt, NULL);
            esp_mqtt_client_start(c);
            started = true;
        }
        while (s_online && s_count > 0) {
            rec_t r = s_q[s_head];
            char json[96];
            int len = snprintf(json, sizeof json, "{\"seq\":%" PRIu32 ",\"t_ms\":%lld,\"temp\":%.1f}", r.seq, r.t_ms, r.temp);
            if (esp_mqtt_client_publish(c, "tenergy/book/sf/data", json, len, 1, 0) < 0) break;
            s_head = (s_head + 1) % QCAP; s_count--;
            ESP_LOGI(TAG, "ส่ง %s (เหลือ %d)", json, s_count);
        }
        if (!s_online) ESP_LOGI(TAG, "เก็บค่า #%" PRIu32 " ไว้ในคิว (%d/%d)", seq, s_count, QCAP);
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}
