# ex06_pin_to_core

**บทที่ 7** · ผูก task กับ core 0 และ core 1 แล้ววัดเวลา

## รันบนบอร์ดจริง

```bash
idf.py set-target esp32s3
idf.py build
idf.py -p /dev/cu.usbserial-XXXX flash monitor   # ออก: Ctrl + ]
```

> ตัวอย่างนี้ต้องใช้บอร์ดจริง

## ผลที่คาดหวัง (Serial Monitor)

```text
I (...) heavy: เสร็จบน core 1 (x2)
I (...) heavy: เสร็จบน core 0
I (...) heavy: เสร็จบน core 1
I (...) dual: core เดียว: ~2 เท่าของ แยกสอง core
```
