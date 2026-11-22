# ex03_const_static_counter

**บทที่ 4** · const กันแก้ค่า และ static นับสะสม

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
I (...) const_static: เกณฑ์เปิดพัดลม = 32.00 C
I (...) const_static: รอบ 1: plain=1 static=1 total=1
I (...) const_static: รอบ 2: plain=1 static=2 total=2
I (...) const_static: รอบ 3: plain=1 static=3 total=3
```
