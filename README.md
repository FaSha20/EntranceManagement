# مدیریت ورود و خروج بر بستر اینترنت اشیا

### شرح پروژه:

در این پروژه قصد داریم تا سامانه ای جهت کنترل لحظه ای ورود و خروج افراد به یک شرکت فرضی را بر بستر اینترنت اشیا پیاده سازی کنیم. چنین سامانه ای متشکل تشکل از بخشهای زیر خواهد بود:
<br/><br/>
- سامانه نهفته شامل سنسورها و ماژولهای سخت افزاری

- ابر (cloud) که در این تمرین یک وب سرور ساده در نظر گرفته میشود

- سیستم نظارتی (نرم افزاری جهت مشاهده رویدادهای سامانه به شکل لحظه ای)
<br/><br/>
در ادامه، توضیحات، کدها و گزارشات مربوط به هرکدام از بخش ها آورده خواهد شد. 
<br/><br/>
## بخش اول: سامانه نهفته نصب شده در محل 
توضیحات بخش: 
<br/><br/>
جهت شناسایی کارمندان از سنسور و تک RFID استفاده میشود. هر RFID tag برابر با هویت یک فرد است. در ورودی شرکت یک RFID sensor قرار دارد که با استفاده از آن میتوان مشخصات افراد را از روی RFID tag خواند. این مشخصه یک کد 10 رقمی است. 
<br/><br/>
باز و بسته شدن در شرکت به وسیله یک motor servo کنترل میشود. همچنین مقابل در، یک چراغ LED و یک مانیتور وجود دارد. LED با 
توجه به اجازه ورود به دو رنگ قرمز یا سبز در میآید، در همین هنگام مشخصات فرد بر روی مانیتور نمایش داده میشود. 
<br/><br/>
برای ارتباط با شبکه ی اینترنت و ارسال داده نیاز به یک سخت افزار جهت ارسال و دریافت داده به صورت بی سیم داریم که این کار با ماژول ESP8266 wifi انجام میشود. 
<br/><br/>
در نهایت کنترل تمامی این ماژولها بهوسیله یک برد Arduino انجام میشود
<br/><br/>
### بخش اول: خواندن RFID و ارسال برای سرور 
![image (9)](https://github.com/FaSha20/EntranceManagement/assets/114980788/729d6fb1-c6c3-4229-9249-15a4d9c4c5b8)
<br/><br/>
همانطور که در تصویر بالا مشاهده میکنیم، این بخش از یک ماژول آردوینو، یک ماژول اترنت برای ارسال پکتها و ارتباط با سرور، و یک ترمینال مجازی برای شبیه سازی دریافت RFID ها، و دو لامپ قرمز و سبز داریم.
<br/><br/>
![image (7)](https://github.com/FaSha20/EntranceManagement/assets/114980788/8ad16fbf-eba3-4b4c-adee-5300a5ef53a4)
<br/><br/>
در اینجا میبینیم که کد داده شده به برد آردوینو کامپایل شده و درحال گرفتن ورودی است. 
<br/><br/>
![image](https://github.com/FaSha20/EntranceManagement/assets/114980788/6f707b9b-a74d-4fdd-827c-f11df87e10a7)
<br/><br/>
پس از اینکه در ترمینال ورودی را وارد کردیم، در اینجا نتیجه را مشاهده میکنیم. اگر به آدرس 192.168.2.2 ریکوئست GET زده شود، به ما پکتی برمی گرداند که در خود محتوای RFID خوانده شده را دارد. در عکس بعدی هدر پکت را میبینیم و مشاهده میکنیم که آیدی داده شده ارسال شده است. 
<br/><br/>
![image (2)](https://github.com/FaSha20/EntranceManagement/assets/114980788/ab8892b5-5ba1-4973-b6b4-60af3406bb99)
<br/><br/>
در ادامه به توضیح کد این بخش میپردازیم:
<br/><br/>
![image (3)](https://github.com/FaSha20/EntranceManagement/assets/114980788/bd70f41e-6b30-4757-92ca-7048fde8acd5)
<br/><br/>
از کتابخانه Ethercard استفاده میکنیم. مقادیر constant، آدرس مک، myip (آی پی که ما با آن شناخته میشویم)، gwip (آی پی اترنت که از طریق آن، ماژول اترنت با سرور ارتباط میگیرد

<br/><br/>
![image (4)](https://github.com/FaSha20/EntranceManagement/assets/114980788/be564b5f-3a97-4c28-b0ef-9d1aab139e8d)
<br/><br/>
در اینجا تابع sendHTTpResponse را داریم که بدنه ریسپانس را میسازد و آیدی گرفته شده در ورودی را به عنوان هدر Authentication قرار میدهد و با تابع ether.httpServerReply آن را ارسال میکند.
<br/><br/>
![image (5)](https://github.com/FaSha20/EntranceManagement/assets/114980788/2e31c94f-e77e-468b-9160-e3204c004c9f)
<br/><br/>
در اینجا تابع خواندن RFID از ترمینال را داریم که تا وقتی ورودی دارد و میخواند، به رشته ورودی اضافه میکند و به char تبدیل میکند و برمیگرداند. 
<br/><br/>
![image (10)](https://github.com/FaSha20/EntranceManagement/assets/114980788/e045d089-6156-44dc-bc6b-9945ca050625)
<br/><br/>
تابع setup را داریم که مقادیر اولیه را روی برد ست میکند. ست کردن پورت های مربوط به LED، چک کردن سایز بافر اترنت که به اندازه کافی باشد، ست کردن آی پی ها روی اترنت و... . این تابع یک بار و در ابتدا اجرا میشود. 
<br/><br/>
![image (6)](https://github.com/FaSha20/EntranceManagement/assets/114980788/c59c20f0-f190-4137-9762-d4cccfe80ecb)
<br/><br/>
تابع loop، تابعی است که مدام در طور برنامه اجرا میشود تا اگر درخواستی وجود دارد، با فراخوانی تابع مربوطه، بخواند و اگر بسته ای رسیده بود، آن را ارسال کند. 
<br/><br/>

### بخش دوم: انجام عملیاتهای مربوطه پس از دریافت نتیجه از سرور

