# ex02_struct_sensor_record

**บทที่ 4** · เก็บข้อมูลเซนเซอร์ด้วย struct และ enum

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

## ผลที่คาดหวัง (Serial Monitor)

```text
I (...) record: จำนวนโซน=3, ขนาด struct=12 bytes
I (...) record: โซน 1: 28.50 C  สถานะ=OK ...
I (...) record: โซน 2: 31.50 C  สถานะ=WARNING ...
I (...) record: โซน 3: 72.00 C  สถานะ=ERROR ...
```
