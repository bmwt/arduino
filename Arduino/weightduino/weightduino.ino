#include "HX711.h"
#include "SSD1306.h"


HX711 scale;
SSD1306  display(0x3c, 5, 4);
void setup() {
  Serial.begin(115200);
  Serial.println("Weightduino");
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_16);
  Serial.println("Initializing the scale");
  display.clear();
  display.drawString(0, 26, "Initializing Scale");
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(10, 128, String(millis()));
  display.display();

  
  // parameter "gain" is ommited; the default value 128 is used by the library
  // HX711.DOUT  - pin #A1
  // HX711.PD_SCK - pin #A0
  scale.begin(25, 26);

  Serial.println("Before setting up the scale:");
  Serial.print("read: \t\t");
  Serial.println(scale.read());     // print a raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println(scale.read_average(20));   // print the average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  Serial.println(scale.get_value(5));   // print the average of 5 readings from the ADC minus the tare weight (not set yet)

  Serial.print("get units: \t\t");
  Serial.println(scale.get_units(5), 1);  // print the average of 5 readings from the ADC minus tare weight (not set) divided
            // by the SCALE parameter (not set yet)

//  scale.set_scale(2280.f);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.set_scale(11400.f);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  // scale.set_scale(0.f);
  scale.tare();               // reset the scale to 0

  Serial.println("After setting up the scale:");

  Serial.print("read: \t\t");
  Serial.println(scale.read());                 // print a raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println(scale.read_average(20));       // print the average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  Serial.println(scale.get_value(5));   // print the average of 5 readings from the ADC minus the tare weight, set with tare()

  Serial.print("get units: \t\t");
  Serial.println(scale.get_units(5), 1);        // print the average of 5 readings from the ADC minus tare weight, divided
            // by the SCALE parameter set with set_scale

  Serial.println("Readings:");
}


void displayWeight(float weight) {
   display.setFont(ArialMT_Plain_24);
   display.setTextAlignment(TEXT_ALIGN_LEFT);
   String stringSuffix = " lbs";
   String displayString = weight + stringSuffix;
   display.setFont(ArialMT_Plain_16);
   display.drawString(0, 0, "Weightduino 0.1");
   display.setFont(ArialMT_Plain_24);
   display.drawString(0, 18, displayString);
   Serial.println(displayString);
}
void loop() {
  Serial.print("one reading:\t");
  Serial.print(scale.get_units(), 1);
  Serial.print("\t| average:\t");
  float weight = scale.get_units(10);
  display.clear();
  displayWeight(weight);
  display.setTextAlignment(TEXT_ALIGN_RIGHT);
  display.drawString(10, 128, String(millis()));
  display.display();
  Serial.println(weight);
  scale.power_down();             // put the ADC in sleep mode
  delay(5000);
  scale.power_up();
}
