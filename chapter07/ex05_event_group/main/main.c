/*
 * บทที่ 7 ตัวอย่าง 5: event group
 * ระบบส่งข้อมูลขึ้น cloud ได้เมื่อ "Wi-Fi พร้อม" และ "เวลาซิงก์แล้ว" ครบทั้งสองอย่าง
 */
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_log.h"

#define BIT_WIFI_READY  BIT0
#define BIT_TIME_SYNCED BIT1
static EventGroupHandle_t s_eg;

static void wifi_sim(void *arg) { vTaskDelay(pdMS_TO_TICKS(1500)); ESP_LOGI("wifi", "เชื่อมต่อแล้ว"); xEventGroupSetBits(s_eg, BIT_WIFI_READY); vTaskDelete(NULL); }
static void sntp_sim(void *arg) { vTaskDelay(pdMS_TO_TICKS(3000)); ESP_LOGI("sntp", "ตั้งเวลาแล้ว"); xEventGroupSetBits(s_eg, BIT_TIME_SYNCED); vTaskDelete(NULL); }

static void uploader(void *arg)
{
    ESP_LOGI("upload", "รอ Wi-Fi และเวลา...");
    EventBits_t bits = xEventGroupWaitBits(s_eg, BIT_WIFI_READY | BIT_TIME_SYNCED,
                                           pdFALSE,      // ไม่ล้าง bit หลังได้
                                           pdTRUE,       // รอครบทุก bit
                                           pdMS_TO_TICKS(10000));
    if ((bits & (BIT_WIFI_READY | BIT_TIME_SYNCED)) == (BIT_WIFI_READY | BIT_TIME_SYNCED)) {
        ESP_LOGI("upload", "พร้อมแล้ว เริ่มส่งข้อมูล");
    } else {
        ESP_LOGE("upload", "หมดเวลารอ (bits=0x%x)", (unsigned)bits);
    }
    vTaskDelete(NULL);
}

void app_main(void)
{
    s_eg = xEventGroupCreate();
    xTaskCreate(uploader, "uploader", 3072, NULL, 5, NULL);
    xTaskCreate(wifi_sim, "wifi_sim", 2048, NULL, 5, NULL);
    xTaskCreate(sntp_sim, "sntp_sim", 2048, NULL, 5, NULL);
}
