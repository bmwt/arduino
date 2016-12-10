#include <Ports.h>
#include <RF12.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "sensorsetup.h"

OneWire oneWire1(ONE_WIRE_BUS);
DallasTemperature dallas1(&oneWire1);

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
int sensor1Count=0;

void setup () 
 {
 dallas1.begin();
 rf12_initialize(nodeNumber, RF12_915MHZ, 212);
 outData.nodenumber=nodeNumber;
 }

static void consumeInData () 
{
 }

static byte produceOutData () 
{
  sensor1Count++;
  if (sensor1Count > 2000 )
 {
 dallas1.requestTemperatures();
 outData.payloadtype=1;
 outData.value1=dallas1.getTempFByIndex(0);
 return 1;
 }
}

void loop () 
{
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
