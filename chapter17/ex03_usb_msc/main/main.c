/*
 * บทที่ 17 ตัวอย่าง 3: USB Mass Storage (MSC)
 * แบ่งพื้นที่ flash 7 MB (พาร์ทิชัน storage) ให้คอมพิวเตอร์เห็นเป็นไดรฟ์ ESP32S3
 * สลับเจ้าของได้ทีละฝ่าย:  กดปุ่ม BOOT = ให้ "โปรแกรม" ใช้ (เขียน log.txt) / กดอีกครั้ง = คืนให้ "คอมพิวเตอร์"
 * ห้ามเขียนจากทั้งสองฝ่ายพร้อมกัน เพราะ FAT ไม่รู้ว่าอีกฝ่ายแก้ไขอะไร ไฟล์ระบบจะพัง
 */
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_partition.h"
#include "wear_levelling.h"
#include "tinyusb.h"
#include "tinyusb_default_config.h"
#include "tinyusb_msc.h"
#include "esp_timer.h"
#include "esp_log.h"

#define BTN_GPIO GPIO_NUM_0
static const char *TAG = "msc";
static tinyusb_msc_storage_handle_t s_storage;

static void on_storage_event(tinyusb_msc_storage_handle_t h, tinyusb_msc_event_t *e, void *arg)
{
    if (e->id == TINYUSB_MSC_EVENT_MOUNT_COMPLETE)
        ESP_LOGI(TAG, "ตอนนี้ไดรฟ์เป็นของ: %s", e->mount_point == TINYUSB_MSC_STORAGE_MOUNT_APP ? "โปรแกรม (/data)" : "คอมพิวเตอร์");
    else if (e->id == TINYUSB_MSC_EVENT_MOUNT_FAILED || e->id == TINYUSB_MSC_EVENT_FORMAT_REQUIRED)
        ESP_LOGE(TAG, "mount ไม่ได้ หรือต้องฟอร์แมต");
}

static void append_log(void)
{
    FILE *f = fopen("/data/log.txt", "a");
    if (!f) { ESP_LOGE(TAG, "เปิดไฟล์ไม่ได้"); return; }
    fprintf(f, "uptime %lld s\n", esp_timer_get_time() / 1000000);
    fclose(f);
    ESP_LOGI(TAG, "เขียน /data/log.txt แล้ว");
}

void app_main(void)
{
    gpio_config_t io = { .pin_bit_mask = 1ULL << BTN_GPIO, .mode = GPIO_MODE_INPUT, .pull_up_en = GPIO_PULLUP_ENABLE };
    ESP_ERROR_CHECK(gpio_config(&io));

    const esp_partition_t *part = esp_partition_find_first(ESP_PARTITION_TYPE_DATA, ESP_PARTITION_SUBTYPE_DATA_FAT, "storage");
    if (!part) { ESP_LOGE(TAG, "ไม่พบพาร์ทิชัน storage ตรวจ partitions.csv"); return; }
    static wl_handle_t wl = WL_INVALID_HANDLE;
    ESP_ERROR_CHECK(wl_mount(part, &wl));                 // wear levelling: กระจายการเขียนไม่ให้ flash บางจุดสึกเร็ว

    tinyusb_msc_storage_config_t sc = {
        .medium.wl_handle = wl,
        .mount_point = TINYUSB_MSC_STORAGE_MOUNT_USB,     // เริ่มต้นให้คอมพิวเตอร์ใช้
        .fat_fs = { .base_path = "/data", .config.max_files = 4, .config.format_if_mount_failed = true },
    };
    ESP_ERROR_CHECK(tinyusb_msc_new_storage_spiflash(&sc, &s_storage));
    ESP_ERROR_CHECK(tinyusb_msc_set_storage_callback(on_storage_event, NULL));

    const tinyusb_config_t tusb_cfg = TINYUSB_DEFAULT_CONFIG();
    ESP_ERROR_CHECK(tinyusb_driver_install(&tusb_cfg));
    ESP_LOGI(TAG, "เสียบพอร์ต USB แล้วจะเห็นไดรฟ์ใหม่ (%lu KB)", (unsigned long)(part->size / 1024));

    bool app_owns = false;
    while (1) {
        if (gpio_get_level(BTN_GPIO) == 0) {
            app_owns = !app_owns;
            ESP_ERROR_CHECK(tinyusb_msc_set_storage_mount_point(s_storage,
                            app_owns ? TINYUSB_MSC_STORAGE_MOUNT_APP : TINYUSB_MSC_STORAGE_MOUNT_USB));
            if (app_owns) append_log();
            while (gpio_get_level(BTN_GPIO) == 0) vTaskDelay(pdMS_TO_TICKS(20));
        }
        vTaskDelay(pdMS_TO_TICKS(20));
    }
}
