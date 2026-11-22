# บทที่ 15 Debugging, Testing และการจัดการ Source Code

ตัวอย่างประกอบบทที่ 15 ของหนังสือ

## หัวข้อในบท

15.1 หลักการ debug ที่ใช้ได้ทุกปัญหา  
15.2 Debug ด้วย JTAG ผ่านพอร์ต USB  
15.3 อ่าน panic และ backtrace  
15.4 Core dump: กล่องดำของ firmware  
15.5 Unit test  
15.6 Git และ CI ด้วย GitHub Actions  
15.7 ฝังเลขเวอร์ชันใน firmware

## ตัวอย่าง

| โฟลเดอร์ | สิ่งที่ทำ | รัน | สถานะ |
|---|---|---|---|
| `ex01_jtag_breakpoint` | หยุดโปรแกรมด้วย breakpoint | บอร์ดจริงเท่านั้น | [เปิด](ex01_jtag_breakpoint/) |
| `ex02_panic_backtrace` | จงใจทำให้ crash แล้วอ่าน backtrace | Wokwi + บอร์ดจริง | [เปิด](ex02_panic_backtrace/) |
| `ex03_core_dump` | เก็บ core dump ไว้วิเคราะห์ | บอร์ดจริงเท่านั้น | [เปิด](ex03_core_dump/) |
| `ex04_unit_test` | ทดสอบฟังก์ชันอัตโนมัติ | Wokwi + บอร์ดจริง | [เปิด](ex04_unit_test/) |
| `ex05_ci_build` | ตั้ง GitHub Actions ให้ build ทุก commit | — | [เปิด](ex05_ci_build/) |
| `ex06_version_info` | แสดงเวอร์ชันและเวลา build | Wokwi + บอร์ดจริง | [เปิด](ex06_version_info/) |
