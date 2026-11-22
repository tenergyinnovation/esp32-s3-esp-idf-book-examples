/*
 * บทที่ 16 ตัวอย่าง 3: ตรวจสถานะความปลอดภัย
 * โปรแกรมนี้ "อ่าน" สถานะเท่านั้น ไม่เขียน eFuse ใดๆ ปลอดภัยที่จะรันบนบอร์ดทดลอง
 * การเปิด Secure Boot / Flash Encryption จริงเป็นการเขียน eFuse ถาวร ย้อนกลับไม่ได้
 */
#include "esp_secure_boot.h"
#include "esp_flash_encrypt.h"
#include "esp_chip_info.h"
#include "esp_log.h"

void app_main(void)
{
    ESP_LOGI("sec", "Secure Boot     : %s", esp_secure_boot_enabled() ? "เปิด" : "ปิด");
    ESP_LOGI("sec", "Flash Encryption: %s", esp_flash_encryption_enabled() ? "เปิด" : "ปิด");
    esp_flash_enc_mode_t m = esp_get_flash_encryption_mode();
    ESP_LOGI("sec", "โหมด            : %s", m == ESP_FLASH_ENC_MODE_DISABLED ? "DISABLED" :
                                          m == ESP_FLASH_ENC_MODE_DEVELOPMENT ? "DEVELOPMENT" : "RELEASE");
    esp_chip_info_t chip; esp_chip_info(&chip);
    ESP_LOGI("sec", "chip revision   : v%d.%d", chip.revision / 100, chip.revision % 100);
    if (!esp_secure_boot_enabled() || !esp_flash_encryption_enabled())
        ESP_LOGW("sec", "อุปกรณ์นี้ยังไม่พร้อมขายจริง: ใครก็อ่าน firmware หรือ flash โปรแกรมอื่นแทนได้");
}
