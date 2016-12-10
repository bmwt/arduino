
//onewire required for dallastemperature

#include <DHT22.h>
#include <LiquidCrystal.h>
#include <math.h>
LiquidCrystal lcd (8, 9, 4, 5, 6, 7);

// setup pins
#define DHT22_PIN A1
DHT22 myDHT22(DHT22_PIN);

//declare
int DhtTempDelay = 500;
int DhtHumidDelay = 500;
int analogPin = A0;
int adc_key_old;
int adc_key_in;
int NUM_KEYS = 5;
int key=-1;
int adc_key_val[5] ={30, 150, 360, 535, 760 };
char msgs[5][15] = {"Right Key OK ",
                   "Up Key OK    ",
                   "Down Key OK  ",
                   "Left Key OK  ",
                   "Select Key OK"};
void setup(void)

{
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("HAIL BRAK");
  lcd.setCursor(0,1);
  lcd.print("Kitchenduino 1.0");
  delay(5000);
  lcd.clear();
  myDHT22.readData(); // init DHT
}

void loop(void)
{ 
//  adc_key_in = analogRead(analogPin);
//  adc_key_in = get_key(adc_key_in);
  lcd.setCursor(0,0);
  printDhtTemp();
  lcd.setCursor(0,1);
  printDhtHumid();
//  lcd.setCursor(0, 1);
//  lcd.print(msgs[adc_key_in]);
  DhtTempDelay++;
  DhtHumidDelay++;
  
}

void printDhtTemp()
{
  if (DhtTempDelay > 499 ) 
  {
  DhtTempDelay = 0;
  lcd.print("Temp:     ");
  lcd.print((getDhtTemp() * 9.0)/ 5.0 + 32.0); // C to F
  lcd.print("F");
  }
}

void printDhtHumid()
{
  if (DhtHumidDelay > 499 )
{
  DhtHumidDelay = 0;
  lcd.print("Humidity: ");
  lcd.print(getDhtHumid());
  lcd.print("%");
}
}
  
int get_key(unsigned int input)
{
  int k;
  for (k = 0; k < NUM_KEYS; k++)
  {
    if (input < adc_key_val[k]) 
    return k;
   
  }
  if (k >= NUM_KEYS)
   k = -1; // No valid key pressed
  return k;
}

float getDhtHumid(){
  myDHT22.readData(); // get DHT values
  return myDHT22.getHumidity();
  }

float getDhtTemp(){
  myDHT22.readData(); // get DHT values
  return myDHT22.getTemperatureC();
  }

