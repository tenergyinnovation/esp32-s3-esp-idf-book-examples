# ex01_data_types

**บทที่ 4** · ชนิดข้อมูลและ sizeof บน ESP32-S3

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
I (...) types: sensor_id=7, temp=-125 (x0.01 C)
I (...) types: samples=123456, humidity=61.5 %
I (...) types: fan_on=false, buf_size=128
I (...) types: sizeof: uint8=1 int16=2 uint32=4 float=4 size_t=4 pointer=4
W (...) types: uint8_t 250 + 10 = 4 (ล้นแล้ววนกลับ)
```
