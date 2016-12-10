// Send out a radio packet every minute, consuming as little power as possible
// 2010-08-29 <jcw@equi4.com> http://opensource.org/licenses/mit-license.php
// $Id: radioBlip.pde 6540 2010-12-24 14:41:03Z jcw $

// all the low-power functions have been moved into the Ports library

#include <Ports.h>
#include <DHT22.h>
#include <RF12.h>
#define DHT22_PIN 4

DHT22 myDHT22(DHT22_PIN);


static word payload;

void setup() {
#ifndef SDCR
    DDRB |= bit(0);
    for (byte i = 0; i < 6; ++i) {
        PINB = bit(0);
        delay(128);
    }
#endif
    rf12_initialize(2, RF12_915MHZ, 212);
}

void loop() {

  DHT22_ERROR_t errorCode;
  errorCode = myDHT22.readData();
 delay(2000);

  payload = myDHT22.getTemperatureC();

  while (!rf12_canSend())

  rf12_recvDone();
    
  rf12_sendStart(0, &payload, sizeof payload);
    
    MilliTimer t;
    while (!t.poll(1000))
        rf12_recvDone();
}
