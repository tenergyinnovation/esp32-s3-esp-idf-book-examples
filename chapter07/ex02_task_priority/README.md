# ex02_task_priority

**บทที่ 7** · ดูผลของ priority เมื่อ task ไม่ยอมพัก

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
I (...) logger: tick ที่ 400 ms
...
W (...) busy: เริ่มงานหนัก 2 วินาที (ไม่ยอมพัก)
(logger หายไป 2 วินาที)
W (...) busy: งานหนักเสร็จ
I (...) logger: tick ที่ 5400 ms
```
