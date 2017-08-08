#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <DHT.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

ESP8266WiFiMulti WiFiMulti;
//sleep
#define SECONDS_DS(seconds) ((seconds)*1000000UL)

//finger


// Config Firebase
#define FIREBASE_HOST "dbms60.firebaseio.com"
#define FIREBASE_AUTH "PuZYC0iRtZEKP1BRgCfNVxhz88i4vMpDs7Sert58"

// Config connect WiFi
//#define WIFI_SSID "Connectify-std"
//#define WIFI_PASSWORD "123456789z"

#define WIFI_SSID "SoKenYo"
#define WIFI_PASSWORD "1234567890"

// Config DHT
#define DHTPIN D3
#define DHTTYPE DHT22

// Set the LCD address to 0x27 in PCF8574 by NXP and Set to 0x3F in PCF8574A
LiquidCrystal_I2C lcd(0x3F, 16, 2);

String name;
DHT dht(DHTPIN, DHTTYPE);
int count = 1;
int fail =1;

void setup() {
  Serial.begin(115200);
  Serial.println("Setup...");
  lcd.begin();
  //lcd.backlight();
  Serial.begin(9600);
  
  WiFi.mode(WIFI_STA);
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  lcd.setCursor(0, 0);
  lcd.print("Connecting");
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    lcd.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  lcd.setCursor(0, 1);
  lcd.print("IP:");lcd.print(WiFi.localIP());
  

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  dht.begin();
  delay(2000);
  lcd.clear();
}

void loop() {
  // Read temp & Humidity for DHT22
  int b = analogRead(A0);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  Serial.println(count);
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    lcd.setCursor(0, 0);
    lcd.print("Failed to read from DHT sensor!");
    
    delay(500);
    lcd.clear();
    return;
  }
  
    if ((WiFiMulti.run() == WL_CONNECTED)) {
    HTTPClient http;
    String url = "http://dbms60.ga/upload.php?temp="+String(t)+String("&humi=")+String(h)+String("&bring=")+String(b);
    Serial.println(url);
    http.begin(url); //HTTP

    int httpCode = http.GET();
    if (httpCode > 0) {
    Serial.printf("[HTTP] GET... code: %d\n", httpCode);
    if (httpCode == HTTP_CODE_OK) {
    String payload = http.getString();
    Serial.println(payload);
    }
    } else {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
    }

  // append a new value to /temperature
   Firebase.setFloat("DHT22/temp", t);
  if (Firebase.failed()) {
      Serial.print("pushing /temperature failed:");
      Serial.println(Firebase.error());  
      return;
  }
  Serial.print("pushed: /temperature/");
  Serial.println(Firebase.getFloat("DHT22/temp"));
  lcd.setCursor(0, 0);
  lcd.print("temp");
  lcd.setCursor(0, 1);
  lcd.print(t,1);lcd.print((char)223);lcd.print("C");

  // append a new value to /temperature
   Firebase.setFloat("DHT22/humi", h);
  if (Firebase.failed()) {
      Serial.print("pushing /humidity failed:");
      Serial.println(Firebase.error());  
      return;
  }
  Serial.print("pushed: /humidity/");
  Serial.println(Firebase.getFloat("DHT22/humi"));
  lcd.setCursor(6, 0);
  lcd.print("humi");
  lcd.setCursor(6, 1);
  lcd.print(h,1);lcd.print("%");
  
  
  // append a new value to /bringnees
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
  
  if(count == 300){
    StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["temperature"] = t;
  root["humidity"] = h;
  root["bringness"] = b;
  
  // append a new value to /logDHT
  String name = Firebase.push("Status/DHT", root);
  // handle error
  if (Firebase.failed()) {
      Serial.print("pushing /Status/DHT failed:");
      Serial.println(Firebase.error());  
      return;
  }
  Serial.print("pushed: /Status/DHT/");
  Serial.println(name);
  count = 1;
  }
  else{
    count = count+1;  
  delay(500);
  }
}
