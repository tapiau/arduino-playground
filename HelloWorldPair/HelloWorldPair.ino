#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
// LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

//LiquidCrystal lcd(8, 11, 16, 17, 18, 19);
//
//LiquidCrystal(rs, rw, enable, d0, d1, d2, d3, d4, d5, d6, d7)
//LiquidCrystal lcd(8, 9, 11, 12, 13, 14, 15, 16, 17, 18, 19);
LiquidCrystal lcd(6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);

char c;
int m;
int s;

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Podaj tekst");
  OSCCAL = 0x4B;
  
  Serial.begin(115200);
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
//  lcd.print(millis() / 1000);
  
  s = (millis()/1000) % 60;
  m = millis()/60000;
  
  if(m<10) lcd.print(0);
  lcd.print(m);
  lcd.print(":");
  if(s<10) lcd.print(0);
  lcd.print(s);  

  if (Serial.available() > 0)
  {
      c = Serial.read(); 
      delay(100);
      Serial.write(c);
      lcd.setCursor(0, 0);
      lcd.print(c,HEX);
  }
}

