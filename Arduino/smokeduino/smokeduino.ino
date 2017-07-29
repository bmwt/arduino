#include "max6675.h"
#include <Wire.h>
#include "SSD1306.h"

int thermoDO = 14;
int thermoCS = 12;
int thermoCLK = 13;

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);
int vccPin = 15;
int gndPin = 16;
SSD1306  display(0x3c, 5, 4); 
void setup() {

  Serial.begin(115200);

  // Initialising the UI will init the display too.
  
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_16);

  Serial.println("Smokeduino 0.1");

  display.clear();
  display.drawString(0, 26, "Smokeduino 0.1");
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(10, 128, String(millis()));
  display.display();
    
  // use Arduino pins 
  pinMode(vccPin, OUTPUT); digitalWrite(vccPin, HIGH);
  pinMode(gndPin, OUTPUT); digitalWrite(gndPin, LOW);
  
  Serial.println("MAX6675 test");
  // wait for MAX chip to stabilize
  delay(2000);
}

void displayTemp() {
//   display.setFont(ArialMT_Plain_10);
   display.setFont(ArialMT_Plain_24);
   display.setTextAlignment(TEXT_ALIGN_LEFT);
   String stringSuffix = " °F";
   String displayString = thermocouple.readFahrenheit() + stringSuffix;
   Serial.print(displayString);
   Serial.println(thermocouple.readFahrenheit());
   display.drawString(0, 26, displayString);
}


void loop() {
  display.clear();
  displayTemp();
  display.setTextAlignment(TEXT_ALIGN_RIGHT);
  display.drawString(10, 128, String(millis()));
  display.display();
  delay(1000);
}
