#include <OneWire.h>
#include <DallasTemperature.h>



// Data wire is plugged into port 4 on the Arduino port 1 D on jee
#define ONE_WIRE_BUS 4

OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);


void setup(void)
{
  // start serial port
  Serial.begin(9600);
  Serial.println("Dallas Temperature IC Control Library Demo");
  sensors.begin();
}

void loop(void)
{ 
  delay(2000);
  sensors.requestTemperatures(); // Send the command to get temperatures
   Serial.print("Dallas_temp: ");
  Serial.print(sensors.getTempCByIndex(0));  

}
