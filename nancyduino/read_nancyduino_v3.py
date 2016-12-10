#!/usr/bin/python
import serial
import time
import sys
import MySQLdb as mdb
ser = serial.Serial('/dev/ttyU0',9600)

conn = mdb.connect('localhost', 'nancyduino', 'nancyduino', 'nancyduino');
cursor = conn.cursor();
cursor.execute("CREATE TABLE IF NOT EXISTS\
	sensordata(ID INT PRIMARY KEY AUTO_INCREMENT,Node INT, Unixtime INT, Temperature FLOAT, Humidity FLOAT)");
conn.commit();
cursor.close();
conn.close();
ser.readline(); # read partial line 

while 1:
 line = ser.readline()
 nodedata = line.split(',')
 node = nodedata[0]
 temp = nodedata[1]
 humidity = nodedata[2]
 conn = mdb.connect('localhost', 'nancyduino', 'nancyduino', 'nancyduino');
 cursor = conn.cursor();
 cursor.execute('insert into sensordata (Node,Unixtime,Temperature,Humidity) values (%s, %s, %s, %s)', (node, int(time.time()), temp, humidity))
 conn.commit();
 cursor.close();
 conn.close();
 print('.')
 