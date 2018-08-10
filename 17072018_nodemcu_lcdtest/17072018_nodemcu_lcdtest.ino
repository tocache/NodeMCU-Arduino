// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 9, en = 10, d4 = 0, d5 = 4, d6 = 5, d7 = 16;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("NodeMCU Online!");
  lcd.setCursor(0, 1);
  lcd.print("Contador:");
}

void loop() {
  lcd.setCursor(9, 1);
  // print the number of seconds since reset:
  lcd.print(millis() / 100);
}
