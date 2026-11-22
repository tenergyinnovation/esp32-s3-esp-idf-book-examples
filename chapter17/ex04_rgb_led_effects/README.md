# ex04_rgb_led_effects

**บทที่ 17** · เอฟเฟกต์ไฟ RGB: rainbow, breathing และไฟสถานะ

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
I (...) rgb: โหมด RAINBOW
I (...) rgb: โหมด BREATHE
I (...) rgb: โหมด STATUS
```

## หมายเหตุ

- ถ้าใช้บอร์ด v1.0 ให้แก้ RGB_GPIO เป็น 48
