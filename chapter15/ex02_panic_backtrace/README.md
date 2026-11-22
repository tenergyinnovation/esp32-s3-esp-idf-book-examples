# ex02_panic_backtrace

**บทที่ 15** · จงใจทำให้ crash แล้วอ่าน backtrace

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
| ปุ่มกด | 1 / 2 | GPIO5 / GND |

## ผลที่คาดหวัง (Serial Monitor)

```text
Guru Meditation Error: Core  0 panic'ed (StoreProhibited). Exception was unhandled.
...
Backtrace: 0x42008a1e:0x3fc9c0f0 0x42008a4b:0x3fc9c110 ...
--- 0x42008a1e: save_reading at .../main/main.c:17
--- 0x42008a4b: app_main at .../main/main.c:33
```
