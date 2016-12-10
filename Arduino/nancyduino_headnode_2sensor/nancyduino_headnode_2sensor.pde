//onewire required for dallastemperature
#include <OneWire.h>
#include <DallasTemperature.h>
#include <DHT22.h>

// setup pins
#define DHT22_PIN 7
#define ONE_WIRE_BUS 2

// setup instances
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DHT22 myDHT22(DHT22_PIN);

//declare
int node_number=1;
void setup(void)

{
  delay(2000);
  // start serial port
  Serial.begin(9600);
  Serial.println("nancyduino root node");
  myDHT22.readData(); // init DHT
  sensors.begin(); // init dallas
}

void loop(void)
{ 
  delay(5000);
  Serial.print("node: ");
  Serial.print(node_number);
  Serial.print(" dalt: ");
  Serial.print(getDallasTemp());
  Serial.print(" dhtt: ");
  Serial.print(getDhtTemp());
  Serial.print(" dhth: ");
  Serial.println(getDhtHumid());
}



float getDallasTemp (){
    sensors.requestTemperatures();
    return sensors.getTempCByIndex(0);
    }

float getDhtHumid(){
  return myDHT22.getHumidity();
  }

float getDhtTemp(){
  myDHT22.readData(); // get DHT values
  return myDHT22.getTemperatureC();
  }
