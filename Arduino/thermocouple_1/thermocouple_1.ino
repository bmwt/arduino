#include <LiquidCrystal.h>
#include <math.h>
#include <MAX6675.h>

int CS = A1;             // CS pin on MAX6675
int SO = A2;              // SO pin of MAX6675
int MAXSCK = A3;             // SCK pin of MAX6675
int units = 2;            // Units to readout temp (0 = raw, 1 = ˚C, 2 = ˚F)
float temperature = 0.0;  // Temperature output variable
LiquidCrystal lcd (8, 9, 4, 5, 6, 7);
MAX6675 temp(CS,SO,MAXSCK,units);

void setup(void)

{
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("HAIL BRAK");
  lcd.setCursor(0,1);
  lcd.print("Kitchenduino 2.0");
  delay(5000);
  lcd.clear();
}

void loop(void)
{ 
	temperature = temp.read_temp();

	if(temperature < 0) {                   
		// If there is an error with the TC, temperature will be < 0
                lcd.setCursor(0,0);
		lcd.print("call bmwt");
		lcd.print( temperature ); 
	} else {
                lcd.setCursor(0,0);
  		lcd.print("Temp: ");
		lcd.print( temperature ); 
	}
 
	// Wait one second before reading again
	delay(2000);	

}
