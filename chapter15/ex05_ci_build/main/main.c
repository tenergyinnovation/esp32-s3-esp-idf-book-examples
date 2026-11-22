/*
 * บทที่ 15 ตัวอย่าง 5: CI
 * ตัวอย่างนี้คือโปรแกรมเล็กๆ ที่ใช้ทดสอบว่า pipeline ทำงาน
 * ไฟล์สำคัญคือ .github/workflows/build.yml ที่รากของ repo (คัดลอกจาก ci/build.yml ในโฟลเดอร์นี้)
 */
#include "esp_log.h"
#include "esp_app_desc.h"

void app_main(void)
{
    const esp_app_desc_t *d = esp_app_get_description();
    ESP_LOGI("ci", "build ผ่าน CI: %s เวอร์ชัน %s (ESP-IDF %s)", d->project_name, d->version, d->idf_ver);
}
