# ex01_i2c_scanner

**บทที่ 9** · ค้นหาอุปกรณ์ทุกตัวบนบัส I2C

## รันบนบอร์ดจริง

```bash
idf.py set-target esp32s3
idf.py build
idf.py -p /dev/cu.usbserial-XXXX flash monitor   # ออก: Ctrl + ]
```

## รันบน Wokwi (VS Code)

1. `idf.py build`
2. Command Palette → **Wokwi: Start Simulator** (อ่าน `wokwi.toml` และ `diagram.json`) หรือเปิด `diagram.json` แล้วกดปุ่มเล่นสีเขียว
3. ถ้าแก้โค้ดแล้ว build ใหม่ Wokwi จะโหลดเฟิร์มแวร์ใหม่เอง ถ้ายังเป็นตัวเก่าให้ปิดแท็บ Wokwi Simulator แล้วเปิดใหม่

## การต่อวงจร

| อุปกรณ์ | ขาอุปกรณ์ | ESP32-S3 |
|---|---|---|
| SHT31 / OLED | SDA | GPIO8 |
| SHT31 / OLED | SCL | GPIO9 |
| SHT31 / OLED | VCC | 3V3 |
| SHT31 / OLED | GND | GND |

## ผลที่คาดหวัง (Serial Monitor)

```text
I (...) scan: เริ่มสแกน I2C...
I (...) scan: พบอุปกรณ์ที่ 0x3C (จอ OLED SSD1306)
I (...) scan: พบอุปกรณ์ที่ 0x44 (SHT31)
I (...) scan: สแกนเสร็จ พบทั้งหมด 2 ตัว
```
