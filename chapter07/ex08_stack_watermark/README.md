# ex08_stack_watermark

**บทที่ 7** · วัดว่า task ใช้ stack ไปเท่าไร

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
I (...) small: เหลือ stack น้อยสุด ~3000 bytes
I (...) big: buf[0]=1 เหลือ stack น้อยสุด ~1000 bytes
```

## หมายเหตุ

- ถ้าค่าที่เหลือต่ำกว่าประมาณ 512 bytes ให้เพิ่มขนาด stack [rule of thumb]
