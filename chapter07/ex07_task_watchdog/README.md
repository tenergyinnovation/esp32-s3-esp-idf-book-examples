# ex07_task_watchdog

**บทที่ 7** · ให้ watchdog จับ task ที่ค้าง

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
I (...) worker: ทำงานปกติ รอบ 5
E (...) worker: จำลองค้าง: เลิกรายงานตัว
E (...) task_wdt: Task watchdog got triggered. The following tasks/users did not reset the watchdog in time:
E (...) task_wdt:  - worker (CPU 0/1)
```
