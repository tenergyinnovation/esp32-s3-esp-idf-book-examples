# ex03_softap

**บทที่ 10** · บอร์ดเป็นจุดปล่อย Wi-Fi เอง (SoftAP)

## รันบนบอร์ดจริง

```bash
idf.py set-target esp32s3
idf.py build
idf.py -p /dev/cu.usbserial-XXXX flash monitor   # ออก: Ctrl + ]
```

> ตัวอย่างนี้ต้องใช้บอร์ดจริง

## ผลที่คาดหวัง (Serial Monitor)

```text
I (...) softap: เปิด Wi-Fi "Greenhouse-Setup" รหัส "tenergy123" แล้ว
I (...) softap: มีอุปกรณ์เข้ามา MAC aa:bb:cc:dd:ee:ff
```

## หมายเหตุ

- รหัสผ่าน WPA2 ต้องยาวอย่างน้อย 8 ตัวอักษร
