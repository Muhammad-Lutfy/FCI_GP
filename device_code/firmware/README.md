# Spidy-Draw ESP32 Firmware

ده فولدر كود الجهاز نفسه للـ ESP32.

## المحتويات

- `platformio.ini` إعدادات PlatformIO والبورد.
- `src/` ملفات C++ الرئيسية.
- `include/` ملفات الهيدر والإعدادات.
- `web/` ملفات واجهة الويب الخاصة بالـ ESP لو موجودة.

## التشغيل والرفع على ESP32

افتح Terminal داخل الفولدر ده:

```bash
cd device_code/firmware
pio run
pio run --target upload
```

بعد الرفع، شغل الجهاز واتصل بشبكة الـ ESP32 أو بنفس الشبكة حسب إعداداتك، ثم افتح عنوان الـ ESP من التطبيق.

## Endpoints المستخدمة من تطبيق الموبايل

التطبيق يستخدم ESP URL واحد فقط ويتعامل مع:

- `/status`
- `/upload-text`
- `/execute`
- `/stop`
- `/clear`
- `/home`
- `/servo?pos=0|1`
- `/move?angle=...&repeats=...`

