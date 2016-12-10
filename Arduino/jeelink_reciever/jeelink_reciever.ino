// Serial data over RF12 demo, works in both directions
// 2009-04-17 <jc@wippler.nl> http://opensource.org/licenses/mit-license.php

#include <JeeLib.h>
#include <RF12sio.h>
int nodenumber=10;
RF12 RF12;

void setup() {
    Serial.begin(57600);
    Serial.print("\n[jeelink_receiver]");
    rf12_initialize(nodenumber, RF12_915MHZ, 212);
//    rf12_config();
}

void loop() {
//     if (RF12.poll())
//        Serial.print(RF12.read());
  if (rf12_recvDone()) {
        byte n = rf12_len;
        for (byte i = 0; i < n; ++i) {
            Serial.print(' ');
            Serial.print((int) rf12_data[i]);
        }
        Serial.println();

}
}
