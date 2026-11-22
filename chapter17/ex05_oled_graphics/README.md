# ex05_oled_graphics

**บทที่ 17** · กราฟิกบนจอ OLED: เกจ กราฟเส้น และแอนิเมชัน

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
| OLED | SDA | GPIO8 |
| OLED | SCL | GPIO9 |
| OLED | VCC / GND | 3V3 / GND |
| Potentiometer | SIG | GPIO1 |

## ผลที่คาดหวัง (Serial Monitor)

```text
I (...) gfx: หน้าจอ 1  ค่า 50%  FPS 27
I (...) gfx: หน้าจอ 2  ค่า 52%  FPS 27
I (...) gfx: หน้าจอ 3  ค่า 52%  FPS 28
```

## หมายเหตุ

- FPS ถูกจำกัดโดยความเร็ว I2C: 1 เฟรม = 1024 ไบต์ ที่ 400 kHz ใช้เวลาราว 25 ms จึงได้ประมาณ 25-30 FPS
