# ex06_spi_loopback

**บทที่ 9** · ทดสอบ SPI แบบเชื่อมขา MOSI กับ MISO

## รันบนบอร์ดจริง

```bash
idf.py set-target esp32s3
idf.py build
idf.py -p /dev/cu.usbserial-XXXX flash monitor   # ออก: Ctrl + ]
```

> ตัวอย่างนี้ต้องใช้บอร์ดจริง

## การต่อวงจร

| อุปกรณ์ | ขาอุปกรณ์ | ESP32-S3 |
|---|---|---|
| สายจัมเปอร์ | GPIO11 (MOSI) | GPIO13 (MISO) |

## ผลที่คาดหวัง (Serial Monitor)

```text
I (...) spi: ส่ง: ESP32-S3 SPI OK
I (...) spi: รับ: ESP32-S3 SPI OK
I (...) spi: ผล: ตรงกัน สาย SPI ปกติ
```
