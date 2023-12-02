#include "DHT.h"
#include <LiquidCrystal_I2C.h>

#define DHT_DEVICE 2
#define DHT_TYPE DHT22
//#define DEBUG
DHT dht22(DHT_DEVICE, DHT_TYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2); //

float humidity;
float temperature;
int cnt = 0;
void show_temp_and_hum_in_lcd(LiquidCrystal_I2C *lcd_obj, float temp, float hum)
{
  lcd_obj->setCursor(0, 0);
  lcd_obj->print("Temp ");
  lcd_obj->print(temp);
  lcd_obj->print("C");
  lcd_obj->setCursor(0, 1);
  lcd_obj->print("Humidity ");
  lcd_obj->print(hum);
  lcd_obj->print("%");
}
void setup()
{ 
  #ifdef DEBUG
  Serial.begin(9600);
  Serial.println("Init...");
  #endif
  dht22.begin();
  lcd.init();
  lcd.backlight();
}

void loop()
{
  humidity = dht22.readHumidity();
  temperature = dht22.readTemperature();
  #ifdef DEBUG
  Serial.print("Temp: ");
  Serial.println(temperature);
  Serial.print("Humidity: ");
  Serial.println(humidity);
  #endif
  show_temp_and_hum_in_lcd(&lcd, temperature, humidity);
  delay(1000);
}
