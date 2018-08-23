#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

const int colorR = 255;
const int colorG = 0;
const int colorB = 255;

void setup() 
{
    lcd.begin(16, 1);         // set up the LCD's number of columns and rows:
    lcd.setRGB(colorR, colorG, colorB);
    lcd.setCursor(3,0);
    lcd.print("hello, world!");
    delay(5000);
    lcd.clear();
}

void loop() 
{
    lcd.setCursor(0, 0);      // set the cursor to column 0, line 0
    lcd.print(millis()/1000); // print the number of seconds since reset:
    delay(100);
}
