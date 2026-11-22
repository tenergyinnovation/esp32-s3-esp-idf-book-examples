# ex05_error_handling

**บทที่ 4** · ตรวจ esp_err_t แบบปลอดภัย

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
I (...) errors: GPIO6 -> ESP_OK
E (...) errors: setup_fan_pin(...): GPIO99 ใช้เป็น output ไม่ได้
W (...) errors: GPIO99 -> ESP_ERR_INVALID_ARG : ใช้ค่าสำรองแทน
I (...) errors: ตั้งค่าสำเร็จทั้งหมด
```
