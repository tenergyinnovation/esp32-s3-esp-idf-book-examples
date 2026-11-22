/*
 * บทที่ 15 ตัวอย่าง 6: version info
 * เลขเวอร์ชันมาจากไฟล์ version.txt (หรือ git describe ถ้าไม่มีไฟล์)
 * ใช้ตอบคำถามสำคัญเวลาลูกค้าแจ้งปัญหา: "เครื่องนั้นรัน firmware เวอร์ชันไหน?"
 */
#include "esp_app_desc.h"
#include "esp_log.h"

void app_main(void)
{
    const esp_app_desc_t *d = esp_app_get_description();
    char sha[17];
    esp_app_get_elf_sha256(sha, sizeof sha);
    ESP_LOGI("ver", "โปรเจกต์   : %s", d->project_name);
    ESP_LOGI("ver", "เวอร์ชัน    : %s", d->version);
    ESP_LOGI("ver", "build เมื่อ : %s %s", d->date, d->time);
    ESP_LOGI("ver", "ESP-IDF    : %s", d->idf_ver);
    ESP_LOGI("ver", "ELF SHA256 : %s...", sha);
}
