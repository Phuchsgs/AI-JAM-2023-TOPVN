#include "configs.h"
#include "commons.h"
#include "sensor_driver.h"
#include "lcd_driver.h"
#include "thingspeak_driver.h"

void setup() {
  Serial.begin(9600);
  sensor_init();
  lcd_init();
  thingspeak_init();
}

void loop() {
  sensor_get_data();
  lcd_display_data();
  thingspeak_send_data();
}