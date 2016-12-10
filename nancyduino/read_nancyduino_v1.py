#!/usr/bin/python
import serial
import time
ser = serial.Serial('/dev/tty.usbserial-A800ey1J',9600)
outfile=('/tmp/nancyduino.txt')
while 1:
 f = open (outfile, 'w')
 f.write( str(int(time.time())) + ' ' + ser.readline() )
 f.close()
