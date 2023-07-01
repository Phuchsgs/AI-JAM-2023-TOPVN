#include "MQ135.h"
#include "DHT.h"

 
const int DHTTYPE = DHT11;  
DHT dht(DHTPIN, DHTTYPE);
MQ135 mq135_sensor = MQ135(PIN_MQ135);

void sensor_init(){
  dht.begin(); 
}

void sensor_get_data(){
  tmp = analogRead(acs712Pin);
  tmp = (tmp - 512) * 5.0 / 512 / (0.04 / 0.09) ;
  float h = dht.readHumidity();    
  float t = dht.readTemperature(); 
  float correctedPPM = mq135_sensor.getCorrectedPPM(t, h);

  temperature_c_f = t;
  humidity_f = h;
  gas_ppm_f = correctedPPM;
  current_a_f = tmp;
}