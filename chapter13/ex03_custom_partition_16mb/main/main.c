/*
 * บทที่ 13 ตัวอย่าง 3: partition table ของเราเอง
 * ไฟล์ partitions.csv แบ่ง Flash 16 MB เป็น: nvs, otadata, phy_init, ota_0 (4 MB), ota_1 (4 MB), storage (7 MB)
 * โปรแกรมนี้พิมพ์ตาราง partition ที่ชิปอ่านได้จริง
 */
#include <inttypes.h>
#include "esp_partition.h"
#include "esp_ota_ops.h"
#include "esp_log.h"

static const char *TAG = "part";

void app_main(void)
{
    ESP_LOGI(TAG, "%-10s %-5s %-8s %-10s %-10s", "ชื่อ", "ชนิด", "ชนิดย่อย", "ตำแหน่ง", "ขนาด");
    esp_partition_iterator_t it = esp_partition_find(ESP_PARTITION_TYPE_ANY, ESP_PARTITION_SUBTYPE_ANY, NULL);
    for (; it; it = esp_partition_next(it)) {
        const esp_partition_t *p = esp_partition_get(it);
        ESP_LOGI(TAG, "%-10s %-5s 0x%02x     0x%08" PRIx32 " %6" PRIu32 " KB", p->label,
                 p->type == ESP_PARTITION_TYPE_APP ? "app" : "data", p->subtype, p->address, p->size / 1024);
    }
    esp_partition_iterator_release(it);
    const esp_partition_t *run = esp_ota_get_running_partition();
    ESP_LOGI(TAG, "โปรแกรมกำลังรันจาก partition: %s", run->label);
}
