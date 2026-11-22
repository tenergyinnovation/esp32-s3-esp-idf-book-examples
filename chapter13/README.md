# บทที่ 13 NVS, Partition Table และ File Storage

ตัวอย่างประกอบบทที่ 13 ของหนังสือ

## หัวข้อในบท

13.1 รู้จัก Flash ก่อนเขียน  
13.2 NVS: สมุดจดค่าตั้ง  
13.3 เก็บค่าตั้งทั้งชุดพร้อมเลขเวอร์ชัน  
13.4 Partition table สำหรับ Flash 16 MB  
13.5 ระบบไฟล์ FAT บน Flash  
13.6 Factory reset ด้วยปุ่ม BOOT  
13.7 Data logger แบบ CSV ทนไฟดับ

## ตัวอย่าง

| โฟลเดอร์ | สิ่งที่ทำ | รัน | สถานะ |
|---|---|---|---|
| `ex01_nvs_boot_counter` | นับจำนวนครั้งที่เปิดเครื่องแม้ปิดไฟ | Wokwi + บอร์ดจริง | [เปิด](ex01_nvs_boot_counter/) |
| `ex02_nvs_config_struct` | เก็บค่าตั้งเป็นชุดพร้อมเลขเวอร์ชัน | Wokwi + บอร์ดจริง | [เปิด](ex02_nvs_config_struct/) |
| `ex03_custom_partition_16mb` | ออกแบบ partition table สำหรับ 16 MB | บอร์ดจริงเท่านั้น | [เปิด](ex03_custom_partition_16mb/) |
| `ex04_fatfs_files` | เขียนอ่านไฟล์ใน Flash (FAT) | บอร์ดจริงเท่านั้น | [เปิด](ex04_fatfs_files/) |
| `ex05_factory_reset_button` | กดปุ่มค้างเพื่อล้างค่ากลับโรงงาน | Wokwi + บอร์ดจริง | [เปิด](ex05_factory_reset_button/) |
| `ex06_csv_data_logger` | บันทึกค่าเซนเซอร์เป็นไฟล์ CSV | บอร์ดจริงเท่านั้น | [เปิด](ex06_csv_data_logger/) |
