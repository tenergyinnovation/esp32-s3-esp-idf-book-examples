# ex07_greenhouse_fan_logic

**บทที่ 6** · งานจริง: ควบคุมพัดลมโรงเรือนตามอุณหภูมิ ปุ่ม และเวลา

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
| Potentiometer | SIG / VCC / GND | GPIO1 / 3V3 / GND |
| ปุ่มโหมด | 1 / 2 | GPIO5 / GND |
| LED พัดลม | A ผ่าน 330 Ω | GPIO6 |

## ผลที่คาดหวัง (Serial Monitor)

```text
I (...) greenhouse: อุณหภูมิ 32.4 C -> พัดลม เปิด
I (...) greenhouse: อุณหภูมิ 29.8 C -> พัดลม ปิด
I (...) greenhouse: โหมด: MANUAL (เปิดพัดลมค้าง)
```

## หมายเหตุ

- ในงานจริงให้ใช้โมดูลรีเลย์ที่มีทรานซิสเตอร์และไดโอดกันไฟย้อน ห้ามต่อขดลวดรีเลย์เข้าขา GPIO ตรง
