#!/usr/bin/python
import serial
import time
ser = serial.Serial('/dev/ttyU0',9600)
while 1:
 line = ser.readline()
 nodedata = line.split(',')
 node = nodedata[0]
 temp = nodedata[1]
 humidity = nodedata[2]
 print( str(int(time.time())) + ' ' + str(node) + ' ' + str(temp) + " " + str(humidity) ) 
