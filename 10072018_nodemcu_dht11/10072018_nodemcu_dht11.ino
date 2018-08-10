#include "DHTesp.h"
#include <LiquidCrystal.h>

DHTesp dht;
const int rs = 9, en = 10, d4 = 0, d5 = 4, d6 = 5, d7 = 16;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#define DHT22_PIN 2

int i=0;
byte grado[8] = {
  B11100,
  B10100,
  B11100,
  B00011,
  B00100,
  B00100,
  B00100,
  B00011
};

byte grado2[8] = {
  B11000,
  B11000,
  B00111,
  B01000,
  B01000,
  B01000,
  B00111,
  B00000
};

void setup() {
  dht.setup(2, DHTesp::DHT22);
  lcd.begin(16, 2);
  lcd.createChar(0, grado2);
  //Serial.begin(9600);
}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print("NodeMCU Online!");
  delay(dht.getMinimumSamplingPeriod());
  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();
  delay(70);
//  Serial.print("Temperatura = ");
//  Serial.print(temperature, 1);
//  Serial.println(" C");
//  Serial.print("Humedad = ");
//  Serial.print(humidity, 1);
//  Serial.println(" %");
  lcd.setCursor(0, 1);
  lcd.print("T:");
  lcd.print(temperature, 1);
  lcd.write(byte(0));
  //lcd.write(0xDF);
  //lcd.print("C");
  lcd.setCursor(9, 1);  
  lcd.print("H:");
  lcd.print(humidity, 1);
  lcd.print("%");
  delay(100);
  i=i+1;
  if(i==10){
      slot();
      i=0;
  }
}

void slot() {
  lcd.clear();
  lcd.print("Refreshing");
  lcd.setCursor(0,1);
  lcd.print("display...");
  for(int j=0;j<10;j++) {
    lcd.setCursor(11,0);
    lcd.print(j);
    lcd.print(j);
    lcd.print(j);
    lcd.print(j);
    lcd.print(j);
    lcd.setCursor(11,1);
    lcd.print(j);
    lcd.print(j);
    lcd.print(j);
    lcd.print(j);
    lcd.print(j);
    delay(250);
  }
  delay(250);
  lcd.clear();
}

