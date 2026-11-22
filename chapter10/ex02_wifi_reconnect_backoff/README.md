# ex02_wifi_reconnect_backoff

**บทที่ 10** · หลุดแล้วต่อใหม่แบบเว้นระยะ (exponential backoff)

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
W (...) test: รอบ 1: จำลองสัญญาณหลุด
W (...) wifi: หลุด (reason 8) ลองใหม่ครั้งที่ 1 ในอีก 1 s
I (...) wifi: ได้ IP: 10.10.0.2
I (...) test: รอบ 1: กลับมาออนไลน์แล้ว
```

## หมายเหตุ

- ตั้งชื่อและรหัส Wi-Fi ด้วย `idf.py menuconfig` → **Example Wi-Fi** (ค่าเริ่มต้น `Wokwi-GUEST` สำหรับรันบน Wokwi)
