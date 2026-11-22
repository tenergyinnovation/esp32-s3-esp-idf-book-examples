# ex07_failsafe_state_machine

**บทที่ 14** · งานจริง: พัดลมเข้าสถานะปลอดภัยเมื่อเซนเซอร์เสีย

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
| Potentiometer (จำลองเซนเซอร์) | SIG / VCC / GND | GPIO1 / 3V3 / GND |
| LED พัดลม | A ผ่าน 330 Ω | GPIO6 |

## ผลที่คาดหวัง (Serial Monitor)

```text
W (...) failsafe: สถานะ -> NORMAL (พลาดติดกัน 0)
I (...) failsafe: [NORMAL] T=28.1 C พัดลม=ปิด
W (...) failsafe: สถานะ -> DEGRADED (พลาดติดกัน 1)
...
W (...) failsafe: สถานะ -> FAILSAFE (พลาดติดกัน 5)
I (...) failsafe: [FAILSAFE] T=28.1 C พัดลม=เปิด
```
