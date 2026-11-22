# ex04_rgb_led_onboard

**บทที่ 3** · สั่ง RGB LED บนบอร์ด (GPIO38) เปลี่ยนสี

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
I (...) rgb: สี: แดง
I (...) rgb: สี: เขียว
I (...) rgb: สี: น้ำเงิน
I (...) rgb: สี: ขาว
```

## หมายเหตุ

- ใช้ความสว่างต่ำ (32 จาก 255) เพราะ RGB LED บนบอร์ดสว่างมาก
- component `led_strip` ถูกดาวน์โหลดอัตโนมัติจาก ESP Component Registry ตาม `main/idf_component.yml`
