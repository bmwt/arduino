#include <DHT22.h>
#define DHT22_PIN 7
DHT22 myDHT22(DHT22_PIN);

int node_number=1; // node number

void setup(void)
{
  Serial.begin(9600); // start serial
}

// main loop spits out csv style lines in format node,temp,humidity

void loop(void)
{ 
  delay(300000); // slow down the loop
  myDHT22.readData(); // tell sensor to grab data
  Serial.print(node_number);
  Serial.print(",");
  Serial.print(myDHT22.getTemperatureC());
  Serial.print(",");
  Serial.println(myDHT22.getHumidity());
}

