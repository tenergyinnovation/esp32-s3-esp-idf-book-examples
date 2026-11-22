/*
 * บทที่ 14 ตัวอย่าง 1: PSRAM
 * จอง 2 MB ใน PSRAM (ใหญ่เกิน SRAM ทั้งหมดของชิป) แล้วเทียบความเร็วเขียนกับ SRAM ภายใน
 */
#include <string.h>
#include <inttypes.h>
#include "esp_heap_caps.h"
#include "esp_psram.h"
#include "esp_timer.h"
#include "esp_log.h"

static const char *TAG = "psram";

static int64_t time_memset(uint8_t *p, size_t n)
{
    int64_t t0 = esp_timer_get_time();
    for (int r = 0; r < 10; r++) memset(p, r, n);
    return esp_timer_get_time() - t0;
}

void app_main(void)
{
    if (!esp_psram_is_initialized()) { ESP_LOGE(TAG, "ไม่พบ PSRAM ตรวจ sdkconfig (CONFIG_SPIRAM)"); return; }
    ESP_LOGI(TAG, "PSRAM ทั้งหมด %u KB ว่าง %u KB", (unsigned)(esp_psram_get_size() / 1024),
             (unsigned)(heap_caps_get_free_size(MALLOC_CAP_SPIRAM) / 1024));

    const size_t BIG = 2 * 1024 * 1024;
    uint8_t *big = heap_caps_malloc(BIG, MALLOC_CAP_SPIRAM);
    ESP_LOGI(TAG, "จอง 2 MB ใน PSRAM: %s", big ? "สำเร็จ" : "ไม่สำเร็จ");

    const size_t N = 64 * 1024;
    uint8_t *in  = heap_caps_malloc(N, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
    uint8_t *ext = heap_caps_malloc(N, MALLOC_CAP_SPIRAM);
    if (in && ext) {
        int64_t ti = time_memset(in, N), te = time_memset(ext, N);
        ESP_LOGI(TAG, "เขียน 640 KB: SRAM %lld us, PSRAM %lld us (ช้ากว่า %.1f เท่า)", ti, te, (float)te / ti);
    }
    free(in); free(ext); free(big);
}
