# ex01_usb_cdc

**บทที่ 17** · ทำให้บอร์ดเป็น "พอร์ต COM เสมือน" (USB CDC-ACM)

## รันบนบอร์ดจริง

```bash
idf.py set-target esp32s3
idf.py build
idf.py -p /dev/cu.usbserial-XXXX flash monitor   # ออก: Ctrl + ]
```

> ตัวอย่างนี้ต้องใช้บอร์ดจริง

## ผลที่คาดหวัง (Serial Monitor)

```text
I (...) cdc: พร้อมแล้ว เปิดพอร์ต COM ใหม่ด้วยโปรแกรม terminal ใดก็ได้
I (...) cdc: โปรแกรม terminal เปิดพอร์ตแล้ว (DTR=1)
I (...) cdc: รับ 5 ไบต์ ส่งกลับเป็นตัวพิมพ์ใหญ่
```

## หมายเหตุ

- ต่อสาย USB-C **สองเส้น**: พอร์ต **UART** (ดู log และ flash) กับพอร์ต **USB** (GPIO19/20 ซึ่งเป็นอุปกรณ์ USB ที่เราสร้าง) เมื่อ TinyUSB เริ่มทำงาน พอร์ต USB จะไม่เป็น USB-Serial-JTAG อีกต่อไป จึงต้อง flash ผ่านพอร์ต UART
- Wokwi ยังจำลองอุปกรณ์ USB (TinyUSB) ไม่ได้ ตัวอย่างนี้ต้องทดลองกับบอร์ดจริง
- บน macOS เปิด terminal ด้วย `screen /dev/cu.usbmodem* 115200` (ออกด้วย Ctrl+A แล้ว K)
