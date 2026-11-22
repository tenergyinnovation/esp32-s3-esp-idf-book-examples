# ex06_version_info

**บทที่ 15** · ฝังเลขเวอร์ชันและเวลา build ใน firmware

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
I (...) ver: โปรเจกต์   : ex06_version_info
I (...) ver: เวอร์ชัน    : 1.2.0
I (...) ver: build เมื่อ : Nov 15 2026 10:12:45
I (...) ver: ESP-IDF    : v6.1
I (...) ver: ELF SHA256 : 3f9a1c0b7d2e44a1...
```
