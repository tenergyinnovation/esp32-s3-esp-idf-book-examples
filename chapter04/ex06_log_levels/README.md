# ex06_log_levels

**บทที่ 4** · ใช้ Log ระดับต่างๆ และกรองตาม tag

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
I (...) main: --- ค่าเริ่มต้น (แสดงถึงระดับ Info) ---
E (...) sensor: เซนเซอร์ไม่ตอบ (Error)
W (...) sensor: อุณหภูมิสูงผิดปกติ (Warning)
I (...) sensor: อ่านค่า 28.5 C (Info)
I (...) wifi_app: เชื่อมต่อแล้ว (Info)
I (...) main: --- เปิด Debug เฉพาะ tag sensor ---
...
D (...) sensor: raw=0x6F2A (Debug)
```

## หมายเหตุ

- `CONFIG_LOG_MAXIMUM_LEVEL_DEBUG=y` ใน sdkconfig.defaults ทำให้ข้อความระดับ Debug ถูกคอมไพล์เข้าโปรแกรม (ถ้าไม่ตั้ง ESP_LOGD จะถูกตัดทิ้งตั้งแต่ตอน build)
