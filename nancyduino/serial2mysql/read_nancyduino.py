#!/usr/bin/python
import serial
import time
import sys
import MySQLdb as mdb
ser = serial.Serial('/dev/ttyU0',57600)

ser.readline() # read partial line 

while 1:
 line = ser.readline()
 nodedata = line.split(' ')
 node = nodedata[0]
 temp = nodedata[2]
 conn = mdb.connect('10.20.30.42', 'nancyduino', 'nancyduino', 'nancyduino')
 cursor = conn.cursor()
 cursor.execute('insert into sensordata (Node,Unixtime,Temperature) values (%s, %s, %s)', (node, int(time.time()), temp))
 conn.commit()
 cursor.close()
 conn.close()
 print(temp)
 