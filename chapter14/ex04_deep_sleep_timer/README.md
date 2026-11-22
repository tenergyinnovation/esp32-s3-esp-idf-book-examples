# ex04_deep_sleep_timer

**บทที่ 14** · หลับลึกแล้วตื่นตามเวลา (เครื่องวัดใช้แบตเตอรี่)

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
I (...) deep: ตื่นครั้งที่ 1 สาเหตุ: เปิดเครื่อง/รีเซ็ต
I (...) deep: วัดได้ 28.3 C (ครั้งก่อน 0.0 C)
I (...) deep: หลับลึก 10 วินาที...
(10 วินาทีต่อมา)
I (...) deep: ตื่นครั้งที่ 2 สาเหตุ: ครบเวลา
```
