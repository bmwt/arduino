#!/usr/bin/python
import sys
import MySQLdb as mdb

conn = mdb.connect('localhost', 'nancyduino', 'nancyduino', 'nancyduino');
cursor = conn.cursor();
cursor.execute("CREATE TABLE IF NOT EXISTS\
	sensordata(ID INT PRIMARY KEY AUTO_INCREMENT,Node INT, Unixtime INT, Temperature FLOAT, Humidity FLOAT)");
conn.commit();
cursor.close();
conn.close();
 