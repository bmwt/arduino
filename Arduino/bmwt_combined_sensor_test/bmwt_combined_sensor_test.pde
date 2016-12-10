#include <OneWire.h>
#include <DHT22.h>
#include <DallasTemperature.h>


// Data wire is plugged into port 7 on the Arduino
// Connect a 4.7K resistor between VCC and the data pin (strong pullup)
#define DHT22_PIN 7
// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 2

// Setup a DHT22 instance
DHT22 myDHT22(DHT22_PIN);
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);


void setup(void)
{
  // start serial port
  Serial.begin(9600);
  Serial.println("DHT22 and Dallas Temperature IC Control Library Demo");
  sensors.begin();
}

void loop(void)
{ 
  DHT22_ERROR_t errorCode;

  delay(2000);
  sensors.requestTemperatures(); // Send the command to get temperatures
   Serial.print("Dallas_temp: ");
  Serial.print(sensors.getTempCByIndex(0));  
  errorCode = myDHT22.readData();
  switch(errorCode)
  {
    case DHT_ERROR_NONE:
      Serial.print(" DHT_Temp: ");
      Serial.print(myDHT22.getTemperatureC());
      Serial.print(" DHT_Humidity: ");
      Serial.print(myDHT22.getHumidity());
      Serial.println("%");
      break;
    case DHT_ERROR_CHECKSUM:
      Serial.print("check sum error ");
      Serial.print(myDHT22.getTemperatureC());
      Serial.print("C ");
      Serial.print(myDHT22.getHumidity());
      Serial.println("%");
      break;
    case DHT_BUS_HUNG:
      Serial.println("BUS Hung ");
      break;
    case DHT_ERROR_NOT_PRESENT:
      Serial.println("Not Present ");
      break;
    case DHT_ERROR_ACK_TOO_LONG:
      Serial.println("ACK time out ");
      break;
    case DHT_ERROR_SYNC_TIMEOUT:
      Serial.println("Sync Timeout ");
      break;
    case DHT_ERROR_DATA_TIMEOUT:
      Serial.println("Data Timeout ");
      break;
    case DHT_ERROR_TOOQUICK:
      Serial.println("Polled to quick ");
      break;
  }
}
