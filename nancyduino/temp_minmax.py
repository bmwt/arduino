#!/opt/local/bin/python2.7
import time
import sys
import MySQLdb as mdb

try:
 inputdate=sys.argv[1]
 node=sys.argv[2]

except IndexError:
 print "Usage:", sys.argv[0], "YYYYMMDD nodenumber"
 sys.exit()
 
timestart = int(time.mktime(time.strptime(inputdate, "%Y%m%d")))
timeend= timestart + 86399

conn = mdb.connect('caprica.ghostplanet.org', 'nancyduino', 'nancyduino', 'nancyduino')
cursor = conn.cursor();
cursor.execute('select MIN(Temperature) from sensordata where Node = %s and Unixtime between %s and %s', (node, timestart, timeend) )
sqldata= cursor.fetchone()
cursor.close();
conn.commit();
conn.close();
mintemp=int(sqldata[0])

conn = mdb.connect('caprica.ghostplanet.org', 'nancyduino', 'nancyduino', 'nancyduino')
cursor = conn.cursor();
cursor.execute('select MAX(Temperature) from sensordata where Node = %s and Unixtime between %s and %s', (node, timestart, timeend) )
sqldata= cursor.fetchone()
cursor.close();
conn.commit();
conn.close();
maxtemp=int(sqldata[0])

print "%s: %s %s" % (inputdate, mintemp, maxtemp)
