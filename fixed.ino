#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include "DHT.h"
DHT dht;
#define ON_Board_LED 2 
#define DHTTYPE DHT11
#define D7 13 //D8
#define D5 14 //D4

const char* ssid = "Chetda_2.4GHz";
const char* password = "cp66684455";

void setup() {
  Serial.begin(9600);
  delay(500);
  dht.setup(2);
   Serial.println();
  Serial.println("Status\tHumidity (%)\tTemperature (C)\t(F)");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  pinMode(ON_Board_LED,OUTPUT);
  digitalWrite(ON_Board_LED, HIGH);

  pinMode(D5,OUTPUT);
  digitalWrite(D5, LOW);
  pinMode(D7,OUTPUT);
  digitalWrite(D7, LOW);

  //----------------------------------------Wait for connection
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    digitalWrite(ON_Board_LED, LOW);
    delay(250);
    digitalWrite(ON_Board_LED, HIGH);
    delay(250);
  }
  digitalWrite(ON_Board_LED, HIGH); 
  Serial.println("");
  Serial.print("Successfully connected to : ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  delay(2000);
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
    lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Iot Smart Farm");
  int value = analogRead(A0);
  Serial.println(value);
  delay(dht.getMinimumSamplingPeriod());
  float humidity = dht.getHumidity(); // ดึงค่าความชื้น
  float temperature = dht.getTemperature(); // ดึงค่าอุณหภูมิ
  Serial.print(dht.getStatusString());
  Serial.print("\t");
  Serial.print(humidity, 1);
  Serial.print("\t\t");
  Serial.print(temperature, 1);
  Serial.print("\t\t");
  Serial.println(dht.toFahrenheit(temperature), 1);
  lcd.setCursor(2,1);
  lcd.print(String(temperature)+"C");
  delay(1000);
  if(value>=500){
    digitalWrite(D7, LOW);
    Serial.println("off");
  }else{
    digitalWrite(D7, HIGH);
    Serial.println("on");
  }
  delay(1000);

}
