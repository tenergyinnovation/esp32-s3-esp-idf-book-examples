# ex03_custom_partition_16mb

**บทที่ 13** · ออกแบบ partition table สำหรับ Flash 16 MB

## รันบนบอร์ดจริง

```bash
idf.py set-target esp32s3
idf.py build
idf.py -p /dev/cu.usbserial-XXXX flash monitor   # ออก: Ctrl + ]
```

> ตัวอย่างนี้ต้องใช้บอร์ดจริง

## ผลที่คาดหวัง (Serial Monitor)

```text
I (...) part: nvs        data  0x02     0x00009000     24 KB
I (...) part: otadata    data  0x00     0x0000f000      8 KB
I (...) part: phy_init   data  0x01     0x00011000      4 KB
I (...) part: ota_0      app   0x10     0x00020000   4096 KB
I (...) part: ota_1      app   0x11     0x00420000   4096 KB
I (...) part: storage    data  0x81     0x00820000   7168 KB
I (...) part: โปรแกรมกำลังรันจาก partition: ota_0
```
