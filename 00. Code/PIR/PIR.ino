
#include "ThingSpeak.h"   // thư viện sử dụng thingspeak cloud
#include <WiFi.h>         // kết nối internet cho mạch esp32

#define SECRET_SSID "BK Star"
#define SECRET_PASS "bkstar2021"
#define SECRET_CH_ID 2209559
#define SECRET_WRITE_APIKEY "J3EWORUBRSJN1UCT"


char ssid[] = SECRET_SSID;   // your network SSID (name) 
char pass[] = SECRET_PASS;   // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)
WiFiClient  client;

unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;

int inputPin = 15;       // chọn ngõ tín hiệu vào cho PIR
int pirState = LOW;     // Bắt đầu với không có báo động
int val = 0;
void setup()
{
  pinMode(inputPin, INPUT);
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);   
  ThingSpeak.begin(client);  // Initialize ThingSpeak
}
 
void loop()
{
   if(WiFi.status() != WL_CONNECTED)
   {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SECRET_SSID);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass); 
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnected.");
  }   
  ThingSpeak.begin(client);  // Initialize ThingSpeak
  val = digitalRead(inputPin);    // đọc giá trị đầu vào.
  Serial.println(val);
  int x1 = ThingSpeak.writeField(myChannelNumber, 4, val, myWriteAPIKey);
  delay(1000);
  }
 
