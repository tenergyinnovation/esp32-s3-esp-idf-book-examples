# ex05_ci_build

**บทที่ 15** · ตั้ง GitHub Actions ให้ build ทุกตัวอย่างอัตโนมัติ

## รันบนบอร์ดจริง

```bash
idf.py set-target esp32s3
idf.py build
idf.py -p /dev/cu.usbserial-XXXX flash monitor   # ออก: Ctrl + ]
```

> ตัวอย่างนี้ต้องใช้บอร์ดจริง

## ผลที่คาดหวัง (Serial Monitor)

```text
I (...) ci: build ผ่าน CI: ex05_ci_build เวอร์ชัน 1.0.0 (ESP-IDF v6.1)
```

## หมายเหตุ

- ชื่อ Docker image `espressif/idf:v6.1` [ต้องตรวจสอบ] tag ที่มีจริงใน Docker Hub ก่อนใช้
