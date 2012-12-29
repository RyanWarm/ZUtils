#encoding=utf8
import MySQLdb,json

try:
	db = MySQLdb.connect(host="localhost", user="root", passwd="123456", db="zhaopin")
	#db1 = MySQLdb.connect(host="uc05", user="mysql_remoter", passwd="123456", db="zhaopin")
except:
	print "could not connect to MySQL server."
	exit(0)

cursor = db.cursor()

sql = "select id from company_info"

cursor.execute(sql)

fn_profile = open('db_company_ids','w')
ids = []

for row in cursor:
	id = row[0]
	
	ids.append(id)
	continue

	info['id'] = id

	normalized_name = row[2]
	info['normalized_name'] = normalized_name

	sql = "set names utf8; update company_info set normalized_name='" + normalized_name + "'"

	overview = row[4]
	info['overview'] = overview
	if overview:
		sql += ", overview='" + overview + "'"

	location = row[9]
	info['location'] = location
	if location:
		sql += ", location='" + location + "'"

	category = row[10]
	info['category'] = category
	if category:
		sql += ", category='" + category + "'"

	name = row[11]
	info['name'] = name
	if name:
		sql += ", name='" + name + "'"

	property = row[12]
	info['property'] = property
	if property:
		sql += ", property='" + property + "'"

	scale = row[13]
	info['scale'] = scale
	if scale:
		sql += ", scale='" + scale + "'"

	cities = row[14]
	info['cities'] = cities
	if cities:
		sql += ", cities='" + cities + "'"

	sql += " where id=" + str(id) + ";"

	print "processed: " + str(id)

output = json.dumps(ids)
fn_profile.write('%s\n' % (output))

cursor.close()

db.close()

fn_profile.close()
