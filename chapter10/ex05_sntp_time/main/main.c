/*
 * บทที่ 10 ตัวอย่าง 5: SNTP
 * ขอเวลาจาก pool.ntp.org แล้วแสดงเวลาประเทศไทย (UTC+7)
 */
#include <time.h>
#include <sys/time.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_netif_sntp.h"
#include "esp_log.h"
#include "wifi_connect.h"

void app_main(void)
{
    ESP_ERROR_CHECK(wifi_connect(portMAX_DELAY));
    esp_sntp_config_t cfg = ESP_NETIF_SNTP_DEFAULT_CONFIG("pool.ntp.org");
    ESP_ERROR_CHECK(esp_netif_sntp_init(&cfg));
    // lwIP SNTP ส่งคำขอซ้ำเองทุก ~15 s ถ้าแพ็กเก็ต UDP หาย (เครือข่ายช้า/Wokwi public gateway)
    // จึงรอเป็นรอบ ๆ รวมสูงสุด 60 s แทนการรอครั้งเดียว 15 s
    int tries = 0;
    while (esp_netif_sntp_sync_wait(pdMS_TO_TICKS(15000)) != ESP_OK) {
        if (++tries >= 4) {
            ESP_LOGE("time", "ซิงก์เวลาไม่สำเร็จหลังรอ 60 s");
            return;
        }
        ESP_LOGW("time", "ยังไม่ได้เวลา รอรอบที่ %d/4", tries + 1);
    }
    setenv("TZ", "ICT-7", 1);             // เขตเวลาไทย (POSIX: ชื่อ ICT ชดเชย -7 ชั่วโมงจาก UTC)
    tzset();
    while (1) {
        time_t now = time(NULL);
        struct tm t;
        localtime_r(&now, &t);
        char buf[48];
        strftime(buf, sizeof buf, "%Y-%m-%d %H:%M:%S", &t);
        ESP_LOGI("time", "เวลาประเทศไทย: %s", buf);
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}
