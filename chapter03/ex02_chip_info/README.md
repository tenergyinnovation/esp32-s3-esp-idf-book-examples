# ex02_chip_info

**บทที่ 3** · แสดงจำนวน core, ขนาด Flash และ PSRAM ของบอร์ด

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
I (...) chip_info: ชิป: esp32s3
I (...) chip_info: จำนวน core: 2
I (...) chip_info: Wi-Fi: มี, BLE: มี
I (...) chip_info: Flash: 16 MB
I (...) chip_info: PSRAM: 8 MB
I (...) chip_info: heap ว่าง: ... bytes
```

## หมายเหตุ

- บนบอร์ดจริง N16R8 ต้องเห็น Flash 16 MB และ PSRAM 8 MB
