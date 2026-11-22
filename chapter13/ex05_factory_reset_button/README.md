# ex05_factory_reset_button

**บทที่ 13** · กดปุ่ม BOOT ค้าง 3 วินาทีเพื่อล้างค่ากลับโรงงาน

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
| ปุ่ม BOOT บนบอร์ด | — | GPIO0 (มีอยู่แล้ว) |

## ผลที่คาดหวัง (Serial Monitor)

```text
I (...) reset: บูตครั้งที่ 5  กด BOOT ค้าง 3 วินาทีเพื่อล้างค่า
W (...) reset: กดค้าง 1 วินาที...
W (...) reset: กดค้าง 2 วินาที...
E (...) reset: ล้างค่าทั้งหมดและรีสตาร์ต
...
I (...) reset: บูตครั้งที่ 1
```
