# ex03_light_sleep

**บทที่ 14** · งีบสั้นๆ ประหยัดไฟด้วย light sleep

## รันบนบอร์ดจริง

```bash
idf.py set-target esp32s3
idf.py build
idf.py -p /dev/cu.usbserial-XXXX flash monitor   # ออก: Ctrl + ]
```

> ตัวอย่างนี้ต้องใช้บอร์ดจริง

## ผลที่คาดหวัง (Serial Monitor)

```text
I (...) light: รอบ 1 ทำงาน 0.5 s แล้วหลับ 2 s
I (...) light: ตื่นแล้ว หลับไป 2000 ms สาเหตุ=4
```
