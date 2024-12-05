/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 modified 7 Nov 2016
 by Arturo Guadalupi

 This example code is in the public domain.

 https://docs.arduino.cc/learn/electronics/lcd-displays

*/

// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const int trig = 6, echo = 7;
float duration_us, distance_cm, mass, calculations;



void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  //lcd.print("hello, world!");
  Serial.begin (9600);       // initialize serial port
  pinMode(trig, OUTPUT); // set arduino pin to output mode
  pinMode(echo, INPUT);  // set arduino pin to input mode
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  // generate 10-microsecond pulse to TRIG pin
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  // measure duration of pulse from ECHO pin
  duration_us = pulseIn(echo, HIGH);
  mass = 0.0;
  // calculate the distance
  distance_cm = 0.017 * duration_us;
  calculations = distance_cm - 8.13;
  if(calculations < 8.13 - 8.02 && calculations > 0.0){
    mass = 0.0;
  }
  else{
    while(calculations > 0){
      if(calculations > 0.50){
        calculations -= 0.5;
        mass += 39;
      }
      else{
        calculations -= 0.013;
        mass += 4.5;
      }
    }
  }
  // print the value to Serial Monitor
  lcd.print("Weight: ");
  lcd.print(mass);
  lcd.println(" g  ");

  delay(1500);
}