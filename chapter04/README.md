# บทที่ 4 ภาษา C ที่จำเป็นสำหรับ ESP-IDF

ตัวอย่างประกอบบทที่ 4 ของหนังสือ

## หัวข้อในบท

4.1 ชนิดข้อมูลที่รู้ขนาดแน่นอน  
4.2 struct, enum, array และ pointer  
4.3 const และ static  
4.4 volatile: ตัวแปรที่มีคนอื่นแก้ได้  
4.5 จัดการ error ด้วย esp_err_t  
4.6 ระบบ Log  
4.7 ตัวแปรอยู่ที่ไหนในหน่วยความจำ

## ตัวอย่าง

| โฟลเดอร์ | สิ่งที่ทำ | รัน | สถานะ |
|---|---|---|---|
| `ex01_data_types` | ชนิดข้อมูลและ sizeof บน ESP32-S3 | Wokwi + บอร์ดจริง | [เปิด](ex01_data_types/) |
| `ex02_struct_sensor_record` | เก็บข้อมูลเซนเซอร์ด้วย struct และ enum | Wokwi + บอร์ดจริง | [เปิด](ex02_struct_sensor_record/) |
| `ex03_const_static_counter` | const กันแก้ค่า และ static นับสะสม | Wokwi + บอร์ดจริง | [เปิด](ex03_const_static_counter/) |
| `ex04_volatile_button_flag` | volatile กับปุ่มกดผ่าน interrupt | Wokwi + บอร์ดจริง | [เปิด](ex04_volatile_button_flag/) |
| `ex05_error_handling` | ตรวจ esp_err_t แบบปลอดภัย | Wokwi + บอร์ดจริง | [เปิด](ex05_error_handling/) |
| `ex06_log_levels` | ใช้ Log ระดับต่างๆ และกรองตาม tag | Wokwi + บอร์ดจริง | [เปิด](ex06_log_levels/) |
| `ex07_memory_regions` | ดูว่าตัวแปรแต่ละแบบอยู่ตรงไหนในหน่วยความจำ | Wokwi + บอร์ดจริง | [เปิด](ex07_memory_regions/) |
