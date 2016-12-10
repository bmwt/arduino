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
conn = mdb.connect('caprica.ghostplanet.org', 'nancyduino', 'nancyduino', 'nancyduino')
cursor = conn.cursor();
cursor.execute('select Temperature from sensordata where Node = %s and Unixtime between %s and %s order by Unixtime desc limit 1', (node, timethen, timenow) )
sqldata= cursor.fetchone()
cursor.close();
conn.commit();
conn.close();
temperature=int(sqldata[0])
print "Te:%s" % (temperature)
 