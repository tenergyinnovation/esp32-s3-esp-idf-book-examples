# ex04_unit_test

**บทที่ 15** · ทดสอบฟังก์ชันอัตโนมัติด้วย Unity

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
main.c:13:test_cold_stays_off:PASS
main.c:14:test_hot_turns_on:PASS
main.c:15:test_hysteresis_keeps_on:PASS
main.c:16:test_hysteresis_turns_off:PASS
main.c:17:test_invalid_sensor_failsafe:PASS

-----------------------
5 Tests 0 Failures 0 Ignored
OK
```
