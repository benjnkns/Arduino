#include <math.h>
#include <Wire.h>
#include "rgb_lcd.h"
const int B=4275;                 // B value of the thermistor (for alcohol sensor)
const int R0 = 100000;            // R0 = 100k
const int pinTempSensor = A3;     //Temp Sensor Pin
const int pinNoise = A2;          //Noise Sensor Pin

rgb_lcd lcd;                      //Declaring LCD

const int colorR = 255;           //Setting the color of the LCD
const int colorG = 0;
const int colorB = 0;

//Alcohol
#define analogInDatPin 0          //Where the actual percentage is recorded
//Alcohol Sensor SEL Pin is connected to Analog Input Pin 1 (A1). In this case it is used as digital ouput.
//15 is mapped to A1
#define heaterSelPin 15
int sensorValue = 0;              //Initial value

void setup()
{
    Serial.begin(115200);         //Data rate fir Serial Monitor (debugging)
    lcd.begin(16, 2);             //LCD setup
    
    lcd.setRGB(colorR, colorG, colorB); //Set to previously set values above

    pinMode (7, INPUT);           //Button to initiate Alcohol sensor
    pinMode ( 2, OUTPUT);         //Control of Electromagnet
    pinMode(heaterSelPin,OUTPUT); // set the heaterSelPin as digital output.
    digitalWrite(heaterSelPin,HIGH); //when heaterSelPin is set, heater is switched off.
    delay(1000);
}

void loop()
{
  //TEMPERATURE
    int a = analogRead(pinTempSensor );   //Read the temperature sensor's value
    float R = 1023.0/((float)a)-1.0;      //Mathy stuff needed to convert to usable values
    R = 100000.0*R;
    float temperature=1.0/(log(R/100000.0)/B+1/298.15)-273.15;//convert to temperature via datasheet ;
    Serial.print("Temperature: ");        //Print to serial for debugging
    int temp = temperature * (9/5) + 32;  //Convert to Fahrenheit
    Serial.println(temperature * (9/5) + 32); //Print temperature to serial monitor for debugging
   

  //SOUND
    long sum = 0;
    for(int i=0; i<32; i++)             //Loop for precision
    {
        sum += analogRead(pinNoise);    //Add current val to sum
    }
    sum >>= 5;                          //Shift sum by 5 bits to the right
    Serial.print("Noise Level: ");      //Print to serial for debugging
    Serial.println(sum);

  //Alcohol Sensor
    digitalWrite(heaterSelPin,LOW);     //switch on the heater of Alcohol sensor
    sensorValue = analogRead(analogInDatPin); //read the analog value
    Serial.print("sensor test value = ");   //Disply the results in serial monitor.
    Serial.println(1023-sensorValue);  //sensorValue goes down when alcohol is detected. Hence subtracting from 1023.

  //Lock Box
    if (digitalRead(7)==HIGH){        //If the button is pressed
      delay(1000);                    //Gives them time to blow into sensor
      if (1023 - sensorValue > 500){  //Tested level of innebriation
        lcd.print("Too Drunk!!");     //Notify them of the results
        digitalWrite(2,HIGH);         //Keep electromagnet locked
      }   
      else{                           //They are sober enough
        Serial.println("Open");       //
        digitalWrite(2, LOW);         //Turn off electromagnet
      //LCD
        lcd.clear();                  //
        lcd.print("Alcohol Level: "); //Print on LCD
        lcd.setCursor(0, 1);          //Set LED cursor to second level
        lcd.print(1023-sensorValue);  //Print alcohol content sensed on LED
      }
    }
    else{                             //Button has not been pressed
      digitalWrite(2,HIGH);           //Keep box locked
      Serial.println("Locked");
      //LCD
    lcd.clear();                      //
    lcd.print("Fridge Temp: ");       //Print temp to LCD
    lcd.print(temp);
    lcd.setCursor(0, 1);              //Set LED cursor to second level
    lcd.print("Noise Level: ");       //Print noise level to LCD
    lcd.print(sum);
    }
  
    delay(1000);
}
