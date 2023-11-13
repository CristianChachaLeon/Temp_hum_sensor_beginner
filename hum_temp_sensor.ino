#include "DHT.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define DHT_DEVICE 2
#define DHT_TYPE DHT22

DHT dht22(DHT_DEVICE, DHT_TYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2); //

float humidity;
float temperature;
int c = 0;
void show_temp_and_hum_in_lcd(LiquidCrystal_I2C *lcd_obj, float temp, float hum) {
  lcd_obj->setCursor(0, 0);
  lcd_obj->print("Temp ");
  lcd_obj->print(hum);
  lcd_obj->print("C");
  lcd_obj->setCursor(0, 1);
  lcd_obj->print("Humidity ");
  lcd_obj->print(temp);
  lcd_obj->print("%");
}
void setup() {
  Serial.begin(9600);
  Serial.println("Iniciando...");
  dht22.begin();
  lcd.init();
  lcd.backlight();
}

void loop() {
#ifdef SENSOR
  humidity = dht22.readHumidity();
  temperature = dht22.readTemperature();
#else
  humidity = 10;
  temperature = 50;
#endif
  Serial.println(humidity);
  Serial.println(temperature);
  show_temp_and_hum_in_lcd(&lcd, temperature, humidity);
  delay(5000);
}
