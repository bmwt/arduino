// Send out a radio packet every minute, cusuming as little power as possible
// 2010-08-29 <jcw@equi4.com> http://opensource.org/licenses/mit-license.php
// $Id: radioBlip.pde 5976 2010-08-30 09:34:05Z jcw $

// derived from bmp085demo.pde and powerdown_demo.pde

#include <JeeLib.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <avr/sleep.h>
#define ONE_WIRE_BUS 4
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
int nodenumber = 5;
EMPTY_INTERRUPT(WDT_vect); // just wakes us up to resume

static void watchdogInterrupts (char mode) {
    // correct for the fact that WDP3 is *not* in bit position 3!
    if (mode & bit(3))
        mode ^= bit(3) | bit(WDP3);
    // pre-calculate the WDTCSR value, can't do it inside the timed sequence
    byte wdtcsr = mode >= 0 ? bit(WDIE) | mode : 0;
    MCUSR &= ~(1<<WDRF); // only generate interrupts, no reset
    cli();
    WDTCSR |= (1<<WDCE) | (1<<WDE); // timed sequence
    WDTCSR = wdtcsr;
    sei();
}

static void lowPower (byte mode) {
    byte prrSave = PRR, adcsraSave = ADCSRA;
    ADCSRA &= ~ bit(ADEN); // disable the ADC
    PRR = 0xFF;
    // zzzzz...
    SMCR = mode | bit(SE);
    cli();
    MCUCR = MCUCR | bit(BODSE) | bit(BODS); // timed sequence
    MCUCR = MCUCR & ~ bit(BODSE) | bit(BODS);
    sei();
    __asm__ __volatile__ ( "sleep" "\n\t" :: );;
    // re-enable what we disabled
    PRR = prrSave;
    ADCSRA = adcsraSave;
}

static void loseSomeTime (word msecs) {
    // only slow down for periods longer than the watchdog granularity
    while (msecs >= 16) {
        char wdp = 0; // wdp 0..9 corresponds to roughly 16..8192 ms
        while (msecs >= (32 << wdp) && wdp < 9)
            ++wdp;
        watchdogInterrupts(wdp);
        lowPower(SLEEP_MODE_PWR_DOWN);
        watchdogInterrupts(-1); // off
        // adjust the milli ticks, since we will have missed several
        extern volatile unsigned long timer0_millis;
        timer0_millis += 16 << wdp;
        msecs -= 16 << wdp;
    }
}

// End of new power-saving code.

int payload[2];
void setup() {
    rf12_initialize(nodenumber, RF12_915MHZ, 212);
  sensors.begin();

}

void loop() {
  sensors.requestTemperatures();
  
    while (!rf12_canSend())
        rf12_recvDone();
    
    // set the sync mode to 2 if the fuses are still the Arduino default
    // mode 3 (full powerdown) can only be used with 258 CK startup fuses
    //rf12_sendStart(1, &temperature, sizeof temperature, 2); // sync mode!
  payload[1] = (sensors.getTempFByIndex(0));
   //  payload[1] = 100;
    payload[0] = nodenumber;
    rf12_sendStart(1, &payload, sizeof payload, 2);
    rf12_sleep(0);
    loseSomeTime(60000);
    loseSomeTime(60000);
    rf12_sleep(-1);
}

