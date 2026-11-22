# ex02_custom_component

**บทที่ 5** · สร้าง component ไฟจราจรใช้ซ้ำได้

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
| LED แดง | A ผ่าน 330 Ω | GPIO4 |
| LED เหลือง | A ผ่าน 330 Ω | GPIO5 |
| LED เขียว | A ผ่าน 330 Ω | GPIO6 |
| LED ทุกดวง | C | GND |

## ผลที่คาดหวัง (Serial Monitor)

```text
I (...) traffic_light: ไฟ: ดับ
I (...) traffic_light: ไฟ: เขียว
I (...) traffic_light: ไฟ: เหลือง
I (...) traffic_light: ไฟ: แดง
```
