import MySQLdb
import sys,json

fn_ids = open(sys.argv[1])
line = fu_ids.readline()
ids = []

try:
	ids = json.loads(line)
except Exception:
	print "could not load from ids file"
	exit(0)

try:
	db = MySQLdb.connect(host="uc05", user="mysql_remoter", passwd="123456", db="zhaopin")
except:
	print "could not connect to MySQL server."
	exit(0)

cursor = db.cursor()

for id in ids:

	sql = "select * from company_info where id=" + str(id)

	cursor.execute(sql)

	row = cursor.fetchone()

	id = row[0]
	normalized_name = row[2]

	sql = "set names utf8; update company_info set normalized_name='" + normalized_name + "'"

	overview = row[4]
	if overview:
		sql += ", overview='" + overview + "'"

	location = row[9]
	if location:
		sql += ", location='" + location + "'"

	category = row[10]
	if category:
		sql += ", category='" + category + "'"

	name = row[11]
	if name:
		sql += ", name='" + name + "'"

	property = row[12]
	if property:
		sql += ", property='" + property + "'"

	scale = row[13]
	if scale:
		sql += ", scale='" + scale + "'"

	cities = row[14]
	if cities:
		sql += ", cities='" + cities + "'"

	sql += " where id=" + str(id) + ";"

	cursor.execute(sql)

cursor.close()

db.close()
