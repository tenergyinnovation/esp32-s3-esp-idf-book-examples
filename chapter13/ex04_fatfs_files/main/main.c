/*
 * บทที่ 13 ตัวอย่าง 4: ระบบไฟล์ FAT บน Flash
 * ใช้ fopen/fprintf/fgets ภาษา C ปกติได้เลยหลัง mount ที่ /data
 * wear levelling = กระจายการเขียนไปทั่ว Flash ไม่ให้ตำแหน่งเดิมเสื่อมเร็ว
 */
#include <stdio.h>
#include "esp_vfs_fat.h"
#include "esp_log.h"

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

void app_main(void)
{
    fs_mount();
    FILE *f = fopen("/data/hello.txt", "a");               /* "a" = เขียนต่อท้าย */
    if (!f) { ESP_LOGE("fs", "เปิดไฟล์เขียนไม่ได้"); return; }
    fprintf(f, "สวัสดี ESP32-S3 จาก FATFS\n");
    fclose(f);                                              /* ปิดไฟล์ทุกครั้ง ข้อมูลจึงถูกเขียนลง Flash จริง */

    f = fopen("/data/hello.txt", "r");
    char line[96]; int n = 0;
    while (fgets(line, sizeof line, f)) ESP_LOGI("fs", "บรรทัด %d: %s", ++n, line);
    fclose(f);
}
