#include <Ports.h>
#include <RF12.h>
#include "sensorsetup.h"

typedef struct
{
  int nodenumber;
  int payloadtype;
  int value1;
  int value2;
  int value3;
  int value4;
} Payload;

Payload inData, outData;
MilliTimer sendTimer;
byte pendingOutput;

void setup () {
 Serial.begin(57600);
 Serial.print("\n[jeelink_receiver]");
 rf12_initialize(nodeNumber, RF12_915MHZ, 212);
 }

static void consumeInData () {
 Serial.print("Nodenumber:");
 Serial.println(inData.nodenumber);
 Serial.print("Payload Type:");
 Serial.println(inData.payloadtype);
 Serial.print("Value1:");
 Serial.println(inData.value1);
 Serial.print("Value2:");
 Serial.println(inData.value2);
 Serial.print("Value3:");
 Serial.println(inData.value3);
 Serial.print("Value4:");
 Serial.println(inData.value4);

 }

static byte produceOutData () {
  // something about sending data
  // presumably we'd load outData and trigger it by returning 1 instead of 0
  return 0;
}

void loop () {
    if (rf12_recvDone() && rf12_crc == 0 && rf12_len == sizeof inData) {
        memcpy(&inData, (byte*) rf12_data, sizeof inData);
        // optional: rf12_recvDone(); // re-enable reception right away
        consumeInData();
    }

  if (sendTimer.poll(100))
      pendingOutput = produceOutData();

  if (pendingOutput && rf12_canSend()) {
      rf12_sendStart(0, &outData, sizeof outData, 2);
      // optional: rf12_sendWait(2); // wait for send to finish
      pendingOutput = 0;
      }


}
