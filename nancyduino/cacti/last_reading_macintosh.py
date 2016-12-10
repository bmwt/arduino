#!/opt/local/bin/python2.7
import time
import sys
import MySQLdb as mdb
try:
 node=sys.argv[1]

except IndexError:
 print "Usage:", sys.argv[0], "nodenumber"
 sys.exit()

timenow = int(time.time())
timethen = timenow - 300
conn = mdb.connect('10.20.30.42', 'nancyduino', 'nancyduino', 'nancyduino')
cursor = conn.cursor();
cursor.execute('select Temperature,Humidity from sensordata where Node = %s and Unixtime between %s and %s order by Unixtime desc limit 1', (node, timethen, timenow) )
sqldata= cursor.fetchone()
cursor.close();
conn.commit();
conn.close();
temperature=sqldata[0]
humidity=sqldata[1]
print "Temperature:", temperature, "Humidity:", humidity
 