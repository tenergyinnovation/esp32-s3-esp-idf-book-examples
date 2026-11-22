# ex01_multi_file

**บทที่ 5** · แยกโค้ดเป็นหลายไฟล์ .c/.h

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
I (...) main: 25.0 C = 77.0 F  ร้อนเกิน? ไม่
I (...) main: 31.5 C = 88.7 F  ร้อนเกิน? ใช่
I (...) main: 40.0 C = 104.0 F  ร้อนเกิน? ใช่
```
