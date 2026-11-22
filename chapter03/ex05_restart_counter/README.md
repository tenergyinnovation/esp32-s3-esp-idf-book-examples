# ex05_restart_counter

**บทที่ 3** · นับจำนวนครั้งที่รีสตาร์ตและแสดงสาเหตุ

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
I (...) restart: บูตครั้งที่ 1 สาเหตุ: เปิดเครื่อง (power-on) (1)
I (...) restart: รีสตาร์ตใน 5 วินาที
...
I (...) restart: บูตครั้งที่ 2 สาเหตุ: ซอฟต์แวร์สั่ง esp_restart() (3)
```
