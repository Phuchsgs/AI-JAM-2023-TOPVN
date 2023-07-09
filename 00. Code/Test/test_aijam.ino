#include "DHT.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <MQ135.h>
// #include <WiFi.h>
// #include <ThingSpeak.h>
// WiFiClient client;

LiquidCrystal_I2C lcd(0x27,16,2); 


#define PIN_MQ135 34
MQ135 mq135_sensor = MQ135(PIN_MQ135);

// #define SECRET_SSID "BkStar"
// #define SECRET_PASS "Phuc4321"
// #define SECRET_CH_ID 2209662
// #define SECRET_WRITE_APIKEY "9XYZGFXL97JX0L6I"

// char ssid[] = SECRET_SSID;   // your network SSID (name) 
// char pass[] = SECRET_PASS;   // your network password
// int keyIndex = 0;            // your network key Index number (needed only for WEP)
// unsigned long myChannelNumber = SECRET_CH_ID;
// const char * myWriteAPIKey = SECRET_WRITE_APIKEY;

const int buttonPin2 = 33;
const int buttonPin1 = 25;
const int ledPin = 32;
const int dhtPin = 18;
DHT dht(dhtPin, DHT11);
int inputPin = 5;       
int pirState = LOW;     
int val = 0;
const int DHTTYPE = DHT11;

void setup() {
  Serial.begin(9600);
  // WiFi.mode(WIFI_STA);   
  // ThingSpeak.begin(client);
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(inputPin, INPUT);
  pinMode(ledPin, OUTPUT);
  lcd.init();  
  lcd.backlight();
  dht.begin();  
}

int lcd_state_display = 0;

void loop() {
  // if(WiFi.status() != WL_CONNECTED)
  //  {
  //   Serial.print("Attempting to connect to SSID: ");
  //   Serial.println(SECRET_SSID);
  //   while(WiFi.status() != WL_CONNECTED){
  //     WiFi.begin(ssid, pass); 
  //     Serial.print(".");
  //     delay(5000);     
  //   } 
  //   Serial.println("\nConnected.");
  // }   
  // ThingSpeak.begin(client);
  int buttonStatus1 = digitalRead(buttonPin1);
  int buttonStatus2 = digitalRead(buttonPin2);
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  float gas_ppm_f = mq135_sensor.getCorrectedPPM(t, h);
  if (isnan(t)) {
    Serial.println("Failed to read temperature from DHT sensor!");
    return;
  } 
  val = digitalRead(inputPin);
  Serial.println(val);
  if(buttonStatus1==1){
    lcd_state_display = 0;
  }
  if(buttonStatus2==1){
    lcd_state_display = 1;
  }

  if(lcd_state_display == 0){
    lcd.clear();
    Serial.println("BT1");
    digitalWrite(ledPin, HIGH);
    lcd.print("Nhiet do: ");
    lcd.setCursor(9,0);
    lcd.print(t);
    lcd.print(" ");
    lcd.print("C");
    lcd.setCursor(0,1);
    lcd.print("Do am: ");
    lcd.setCursor(9,1);
    lcd.print(h);
    lcd.print(" %");
    delay(1000);
  }
  if(lcd_state_display == 1){
    Serial.println("BT2");
    digitalWrite(ledPin, LOW);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Gas: ");
    lcd.setCursor(9,0);
    lcd.print(gas_ppm_f);
    delay(1000);
  }
  // int x1 = ThingSpeak.writeField(myChannelNumber, 1, t, myWriteAPIKey);
  // int x2 = ThingSpeak.writeField(myChannelNumber, 2, h, myWriteAPIKey);
  // int x3 = ThingSpeak.writeField(myChannelNumber, 3, gas_ppm_f, myWriteAPIKey);
  // int x4 = ThingSpeak.writeField(myChannelNumber, 4, val, myWriteAPIKey);
}
