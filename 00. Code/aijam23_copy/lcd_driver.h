
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27, 16, 2);

void lcd_init(){
  pinMode(8, OUTPUT);
  digitalWrite(8, HIGH);
  lcd.init();
  lcd.backlight();
}

void lcd_display_data(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("PPM: ");
  lcd.print(gas_ppm_f);
  lcd.setCursor(0,1);
  lcd.print("Dong dien: ");
  lcd.print(current_a_f);
  
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Nhiet do: ");
  lcd.print(temperature_c_f);
  lcd.setCursor(0,1);
  lcd.print("Do am: ");
  lcd.print(humidity_f);
  delay(1000);
}