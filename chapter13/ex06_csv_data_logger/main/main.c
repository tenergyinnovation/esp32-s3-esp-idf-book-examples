/*
 * บทที่ 13 ตัวอย่าง 6: data logger
 * บันทึกอุณหภูมิจำลองทุก 2 วินาทีลง /data/log.csv แบบเปิด-เขียน-ปิดทุกครั้ง (ไฟดับก็เสียแค่บรรทัดล่าสุด)
 * เมื่อไฟล์เกิน 64 KB ย้ายเป็น log_old.csv แล้วเริ่มไฟล์ใหม่ (log rotation)
 */
#include <stdio.h>
#include <sys/stat.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_vfs_fat.h"
#include "esp_timer.h"
#include "esp_random.h"
#include "esp_log.h"

#define LOG_PATH "/data/log.csv"
#define OLD_PATH "/data/log_old.csv"
#define MAX_SIZE (64 * 1024)

static wl_handle_t s_wl = WL_INVALID_HANDLE;

static void fs_mount(void)
{
    esp_vfs_fat_mount_config_t cfg = { .format_if_mount_failed = true, .max_files = 4,
                                       .allocation_unit_size = CONFIG_WL_SECTOR_SIZE };
    ESP_ERROR_CHECK(esp_vfs_fat_spiflash_mount_rw_wl("/data", "storage", &cfg, &s_wl));
    uint64_t total = 0, free_b = 0;
    esp_vfs_fat_info("/data", &total, &free_b);
    ESP_LOGI("fs", "mount /data แล้ว ขนาด %llu KB ว่าง %llu KB", total / 1024, free_b / 1024);
}

static void rotate_if_needed(void)
{
    struct stat st;
    if (stat(LOG_PATH, &st) == 0 && st.st_size > MAX_SIZE) {
        remove(OLD_PATH);
        rename(LOG_PATH, OLD_PATH);
        ESP_LOGW("log", "ไฟล์ใหญ่เกิน %d KB หมุนไฟล์แล้ว", MAX_SIZE / 1024);
    }
}

void app_main(void)
{
    fs_mount();
    struct stat st;
    if (stat(LOG_PATH, &st) != 0) {                      /* ไฟล์ใหม่ เขียนหัวตารางก่อน */
        FILE *f = fopen(LOG_PATH, "w"); fprintf(f, "uptime_s,temp_c,hum_pct\n"); fclose(f);
    }
    for (int i = 0; ; i++) {
        rotate_if_needed();
        float t = 25 + (esp_random() % 100) / 10.0f, h = 55 + (esp_random() % 200) / 10.0f;
        FILE *f = fopen(LOG_PATH, "a");
        if (!f) { ESP_LOGE("log", "เขียนไฟล์ไม่ได้"); vTaskDelay(pdMS_TO_TICKS(2000)); continue; }
        fprintf(f, "%lld,%.1f,%.1f\n", esp_timer_get_time() / 1000000, t, h);
        fclose(f);
        if (i % 5 == 0) { stat(LOG_PATH, &st); ESP_LOGI("log", "บันทึกแล้ว ไฟล์ขนาด %ld bytes", (long)st.st_size); }
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}
