# ex03_oled_text

**บทที่ 9** · แสดงข้อความบนจอ OLED

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
I (...) oled: แสดงวินาทีที่ 0
I (...) oled: แสดงวินาทีที่ 1
```
