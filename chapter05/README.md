# บทที่ 5 ระบบ Build, Component และ Configuration

ตัวอย่างประกอบบทที่ 5 ของหนังสือ

## หัวข้อในบท

5.1 ระบบ build ทำงานอย่างไร  
5.2 แยกโค้ดหลายไฟล์  
5.3 สร้าง component ของเราเอง  
5.4 เมนูตั้งค่าของเราเองด้วย Kconfig  
5.5 sdkconfig.defaults: ค่าตั้งที่ติดไปกับโปรเจกต์  
5.6 Component จาก Registry  
5.7 ขนาด firmware

## ตัวอย่าง

| โฟลเดอร์ | สิ่งที่ทำ | รัน | สถานะ |
|---|---|---|---|
| `ex01_multi_file` | แยกโค้ดเป็นหลายไฟล์ .c/.h | Wokwi + บอร์ดจริง | [เปิด](ex01_multi_file/) |
| `ex02_custom_component` | สร้าง component ไฟจราจรใช้ซ้ำได้ | Wokwi + บอร์ดจริง | [เปิด](ex02_custom_component/) |
| `ex03_kconfig_option` | เพิ่มเมนูตั้งค่าเองใน menuconfig | Wokwi + บอร์ดจริง | [เปิด](ex03_kconfig_option/) |
| `ex04_sdkconfig_defaults` | ตั้งค่า Flash 16 MB และ PSRAM ด้วย sdkconfig.defaults | บอร์ดจริงเท่านั้น | [เปิด](ex04_sdkconfig_defaults/) |
| `ex05_managed_component` | ใช้ component led_strip จาก Registry | Wokwi + บอร์ดจริง | [เปิด](ex05_managed_component/) |
| `ex06_build_size_report` | อ่านรายงานขนาดโปรแกรม idf.py size | Wokwi + บอร์ดจริง | [เปิด](ex06_build_size_report/) |
