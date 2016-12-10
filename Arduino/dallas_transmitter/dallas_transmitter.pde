// Send out a radio packet every minute, consuming as little power as possible
// 2010-08-29 <jcw@equi4.com> http://opensource.org/licenses/mit-license.php
// $Id: radioBlip.pde 6540 2010-12-24 14:41:03Z jcw $

// all the low-power functions have been moved into the Ports library

#include <Ports.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <RF12.h>
#define ONE_WIRE_BUS 4

char payload[5];
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {
#ifndef SDCR
    DDRB |= bit(0);
    for (byte i = 0; i < 6; ++i) {
        PINB = bit(0);
        delay(128);
    }
#endif

rf12_initialize(3, RF12_915MHZ, 212);
sensors.begin();
}

void loop() {

 delay(2000);

  sensors.requestTemperatures();
  float temp_f = sensors.getTempFByIndex(0);
  int temp_f10 = (temp_f * 10.0);
  while (!rf12_canSend())

  rf12_recvDone();
    
  rf12_sendStart(0, &temp_f10, sizeof temp_f10);
    
    MilliTimer t;
    while (!t.poll(1000))
        rf12_recvDone();
}

