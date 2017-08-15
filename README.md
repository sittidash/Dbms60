# Dbms60   

web : https://www.dbms60.ga/ 



<a href="http://www.mx7.com/view2/A3hc7qUGRyqcF7xy" target="_blank"><img border="0" src="http://www.mx7.com/i/194/1MaElJ.jpg" /></a>


# อุปกรณ์ 
1. NodeMCU เอาไว้รับค่าข้อมูลและส่งเข้าไปใน cloue Server
2. Senser DHT22 ไว้ตรวจสอบค่าความชึ้นและอุณหภูมิแล้ว ส่งเข้าไปในบอร์ด NodeMCU
3. LDR ใช้วัดว่าความสว่าง แล้วส่งเข้าบอ์ด NodeMCU
4. จอ LCD ไว้แสดงค่าที่ได้รับจาก NodeMCU

#####รายละเอียดรายต่อวงจรและใช้งานเบื้องต้น#####


# 1.วงจรการต่อ NodeMCU กับ Sensor LCD และ DHT22 และ LDR

# ทำการต่อ NodeMCU เข้ากับ DHT22 แบบ โดย

1.ขา1-VCC => ขา Vin(3.3v) ของ NodeMCU

2.ขา2-DIGTAL => ขา D3 ของ NodeMCU

3.ขา3-NULL => NULL ของ NodeMCU

4.ขา4-GND => ขา ของ NodeMCU 

# ทำการต่อ NodeMCU เข้ากับ Sensor LCD แบบ I2C โดย

1.ขา1-GND => ขา GND ของ NodeMCU

2.ขา2-VCC => ขา Vin(5.5v) ของ NodeMCU

3.ขา3-SDA => ขา D2 ของ NodeMCU

4.ขา4-SCL => ขา D1 ของ NodeMCU


# ทำการต่อNodeMCU เข้ากับ LDR

1.ขาA0 => ขา 3V และ LDR 1 ขา

2.ขา2-LDR => ขา GND  ดังรูป

<a href="http://www.mx7.com/view2/A3hdjSrUpy95uzzR" target="_blank"><img border="0" src="http://www.mx7.com/i/28c/tgWl3a.jpg" /></a>


# 2.สมัคร Domain Name กับเขียว SHA256

ทำการสมัคร Domain name โดยสมัครที่เว็ป Namecheap จำกนั้นก็ทำการตั้งค่าใน Domain name ที่เราสมัคร โดยเข้าไปที่ Advance DNS ทำการเพิ่ม HOST Record Type HOST Value TTL
1. A Record / @ / IP address / Auto

2. URL Redirect Record / @ / Domain name / Unmasked

# เมื่อทำการสมัคร Domain name ได้แล้วทำการเข้ารหัสเขียว SHA (https://) โดยทำการเข้าไปที่ Server ของเรา และทำการลง SHA โดยใช้ Certbot

INSTALL

$ sudo apt-get update

$ sudo apt-get install software-properties-common

$ sudo add-apt-repository ppa:certbot/certbot

$ sudo apt-get update 

$ sudo apt-get install python-certbot-apache 

Get Started 

$ sudo certbot –apache 

$ sudo certbot --apache certonly 

เมื่อทำการลง Certbot จะให้ใส่ E-mail และ Domain name ของเรา ถ้ายังไม่ได้สมัคร Domain จะไม่สารมารถทำการเข้ารหัส SHA ได้ 


# 3.Set up Firebase

1.สมัคร Firebase และทำการ เพิ่มโครงการ ตั้งชื่อโครงการของเรา

2.หลังจากตั้งชื่อโครงการของเราแล้ว จะได้หน้า Console ของ โครงการที่เราสร้างไป

3.ให้เลือกเมนู Database จากนั้นไปที่ Tab RULES เพื่อเข้าจัดการ Users authorized ของการเข้าถึงข้อมูล เบื้องต้นเราจะอนุญาตให้คนที่เรียกเข้าถึงข้อมูลได้หมดทั้ง Read และ Write ข้อมูลได้ โดยแก้ไข Code แล้ว กดปุ่ม PUBLIC เพื่อบันทึกกำรเปลี่ยนแปลง

<a href="http://www.mx7.com/view2/A3hfQd4FsJBNP8r8" target="_blank"><img border="0" src="http://www.mx7.com/i/1e6/ym2gm2.png" /></a>

4.กลับมาที่ Tab Data เพื่อลองสร้างข้อมูล โดยคลิกที่เครื่องหมาย +

5.กดไปที่เมนู Home Overview ของ Project ที่เราสร้าง และ คลิกเลือกที่ Add Firebase To Your web app

6.ในที่นี้ NodeMCU จะทำส่งข้อมูลเข้าไปที่ WebServer ก่อนและ Server ทำการส่งค่าไปยัง Firebase ด้วย RESTFUL API (Method PUT)

<a href="http://www.mx7.com/view2/A3hghvrbitkBpdNG" target="_blank"><img border="0" src="http://www.mx7.com/i/212/KIOTSe.png" /></a>

# 4.Set up mySQL

1.ทำการลง ติดตั้ง Apache2 / PHP7.0 / MySQL / phpMyadmin

2.เข้าที่ phpMyadmin และทำการสร้างฐานข้อมูลแบบ utf8_unicode_ci โดยจะมีฐานข้อมูลชื่อ temp / humid / record 

Temp = อุณหภูมิ / varchar(5) 

humid = ควำมชื้น / varchar(5) 

bright = ความสว่าง /vaechar(5)

3.NodeMCU ส่งข้อมูลเข้าไปยัง WebServer 

#define web_server "http://104.199.xx.xx/" // IP web server 

Voidloop

HTTPClient http; 

http.begin(web_server);

http.addHeader("Content-Type", "application/x-www-form-urlencoded"); 

http.POST("id="+String(id)+","+String(tem)+","+String(hu)); //Sent Data to Database 

String res = http.getString(); 

Serial.println(res);

4.ทำ function บันทึกผลลงบนฐานข้อมูล 

<a href="http://www.mx7.com/view2/A3hgJvL3HmnjHiDs" target="_blank"><img border="0" src="http://www.mx7.com/i/0d9/lmwZWF.png" /></a>

# 5.https:// connection fingerprint 

1.การส่งข้อมูลแบบ https:// ต้องมี fingerprint หาได้โดยการนำ เว็ปของเราไปวางที่เว็ป https://www.grc.com/fingerprints.htm แล้วจะได้ fingerprint มา เช่น DA:F3:84:CC:D9:9A:1C:22:79:EF:C2:B5:88:7F:8A:49:F5:56:0B:3D

2.เขียนโค้ดบน Arduino 

#define web_server " domain name " //IP web server 

#define figger_p " figgerprint " // Figger print grc.com/fingerprints.htm 

ส่วนของ void loop 

http.begin(web_server,figger_p); 

# 6. Sleep mode Hardware+code 

#define SECONDS_DS(seconds) ((seconds)*1000000UL) 
void setup() { 

Serial.begin(115200); 

Serial.println("Setup..."); 

} 

void loop() { 

delay(1000);

Serial.println("Sleeping"); 

ESP.deepSleep(SECONDS_DS(5));

} เมื่ออัพโหลดโคดแล้ว ให้ต่อขำ D0 กับ RST เพื่อให้ทำงำนในโหมด sleep 

<a href="http://www.mx7.com/view2/A3hh9ocQoM1ICfN0" target="_blank"><img border="0" src="http://www.mx7.com/i/1c0/Jb24fX.png" /></a>

# 7.สร้างสรรค์

1.นำ LDR มาประยุกต์ใช้กับวงจร โดยการใช้ LDR วัดค่าความสว่างของแสง

2.หลักการทำงาน เมื่อ LDR วัดค่าแสงสว่างมากๆ ค่่าจะลดลง และถ้าแสงน้อยค่าจะเพิ่มขึ้น  (ค่า LDR จะอยู่ระหว่าง 0-1000)

3.ตัวอยากของโค้ด ที่นำมาใช้งาน

int ldr = analogRead(A0);

void setup()

{

Serial.begin(9600); //start te serial monitor

}


void loop()

{

Firebase.setFloat("DHT22/bring", b);

if (Firebase.failed()) {

Serial.print("pushing /bringnees failed:");

Serial.println(Firebase.error());  

return;

}

Serial.print("pushed: /bringness/");

Serial.println(Firebase.getFloat("DHT22/bring"));

lcd.setCursor(11, 0);

lcd.print("bring");

lcd.setCursor(11, 1);

lcd.print(b,1);

}

}

# 8.MQTT

MQTT คือ Broker ซึ่งเป็นส่วนกลางที่จะนำพาข้อมูลจำกอุปกรณ์ต่างๆ มากองกันไว้ที่ Broker ซึ่งเป็นไปได้ว่าจะมีหลายๆ อุปกรณ์อาจจะเป็น 10 20 ตัว หรืออาจจะ 100 ตัว เชื่อมต่อมาที่ Broker เดียวกัน โดยใช้ Netpie สร้าง Device Key, Session Key โดยตัว Device Key จะเป็นฝั่งของทำง Arduino ส่งเข้าไปยัง NETPIE 

Session Key จะเป็นข้อมูลส่งแบบ Java โดย NETPIE ทำการส่งข้อมูลไปยัง Web ใช้หลักการ Firebase แต่เพียง Netpie เป็น MQTT และสามารถส่งไปหลายๆที่พร้อมกันได้

# 9.แสดงข้อมูล PHP

<a href="http://www.mx7.com/view2/A3hhxQJTXRfou312" target="_blank"><img border="0" src="http://www.mx7.com/i/024/qJB1HZ.png" /></a>


# 10.แสดงข้อมูล Firebase

<a href="http://www.mx7.com/view2/A3hhNrNUrq1LMvkp" target="_blank"><img border="0" src="http://www.mx7.com/i/1cb/IY0rEp.png" /></a>


# จัดทำโดย

1. นายพร้อมพันธ์ ชัยมงคล
2. นายภาณุพงศ์ ไข่คำ
3. นายศุภวิชญ์ วังอะโศก
4. นายสิทธิเดช หมื่นคำแปง
5. นายอุกฤษฎ์ สูตรเลข 

<a href="http://www.mx7.com/view2/A3hi6AEJKMZkjx4c" target="_blank"><img border="0" src="http://www.mx7.com/i/1db/40mUUy.jpg" /></a>

