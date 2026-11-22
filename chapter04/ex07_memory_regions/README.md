# ex07_memory_regions

**บทที่ 4** · ดูว่าตัวแปรแต่ละแบบอยู่ตรงไหนในหน่วยความจำ

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
I (...) memory: stack_buf[64]          0x3fc9....  -> SRAM ภายใน
I (...) memory: s_static_buf[1024]     0x3fc9....  -> SRAM ภายใน
I (...) memory: k_msg (const)          0x3c0.....  -> Flash/อื่นๆ
I (...) memory: malloc(4096)           0x3fc9....  -> SRAM ภายใน
I (...) memory: PSRAM 512 KB           0x3c.....   -> PSRAM
```
