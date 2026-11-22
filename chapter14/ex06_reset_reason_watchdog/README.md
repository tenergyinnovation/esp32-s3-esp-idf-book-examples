# ex06_reset_reason_watchdog

**บทที่ 14** · บันทึกสาเหตุการรีเซ็ตลง NVS เพื่อวิเคราะห์ภาคสนาม

## รันบนบอร์ดจริง

```bash
idf.py set-target esp32s3
idf.py build
idf.py -p /dev/cu.usbserial-XXXX flash monitor   # ออก: Ctrl + ]
```

> ตัวอย่างนี้ต้องใช้บอร์ดจริง

## ผลที่คาดหวัง (Serial Monitor)

```text
I (...) rstlog: สาเหตุครั้งนี้: poweron (เกิดมาแล้ว 1 ครั้ง)
E (...) rstlog: จำลองโปรแกรมค้างโดยปิด interrupt ...
Guru Meditation Error: Core 0 panic'ed (Interrupt wdt timeout on CPU0)
...
I (...) rstlog: สาเหตุครั้งนี้: int_wdt (เกิดมาแล้ว 1 ครั้ง)
```
