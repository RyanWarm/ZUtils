#encoding=utf8
import sys,json,string,chardet

reload(sys)
sys.setdefaultencoding('utf8')
raw = open('/zdisk/data/raw/alignment/user_contact.163', 'r')
email_map = open('./data/email_163ID.data', 'w')
blog_map = open('./data/blog_163ID.data', 'w')
#netID_map = open('./data/163ID_zid.data', 'w')
#zid_map = open('./data/zid_map.data', 'r')
#zid_map_163 = open('./data/zid_map_163.data', 'w')

result = {}
"""
line = zid_map.readLine()
if line:
	result = json.loads(line)
"""
index = 2633290
eMap = {}
wMap = {}
#zMap = {}

#i = 0
for line in raw:
	tmp = line.split('\t')
	if tmp and len(tmp) == 4:
		netID = tmp[0]
		qq = tmp[1]
		blog = tmp[2]
		email = tmp[3]
	
		#qq process
		if qq and qq.isdigit():
			qqMail = qq + '.qq.com'
#			print qqMail + '|qq'	
			eMap[qqMail] = netID
		dot = '.'
		com = '.com'
		cn = '.cn'
		org = '.org'
		if blog and dot in blog and len(blog) > 15 and len(blog) < 50 and (com in blog or cn in blog or org in blog):
			start = string.find(blog, 'http://')
			if start != -1:
				blog = blog[start+7:]
			end = string.rfind(blog, '/')
			if end == len(blog) - 1:
				blog = blog[:len(blog)-1]
			encoding = chardet.detect(blog)
			if encoding['encoding'] == 'gbk' or encoding['encoding'] == 'utf-8' or encoding['encoding'] == 'ascii':
#				blog.decode('gbk').encode('utf-8')
				#print blog + '|blog'
				wMap[blog] = netID
			else:
				print encoding['encoding'] + "---" + blog
		if email and len(email) > 1:
			if string.rfind(email, '\n') == len(email) - 1:
				email = email[:len(email)-1]
#			print email + '|email'
			eMap[email] = netID
		
		#blog process
		#wMap[weiboID] = index

		index += 1
"""		
		i += 1
		if i == 1000:
			break
"""
"""
for i in range(10):
        tmp = {}
        tmp['zid'] = 'z' + str(i)
        result[i] = tmp
"""

output = json.dumps(eMap)
email_map.write('%s\n' % (output))
"""
output = json.dumps(wMap)
netID_map.write('%s\n' % (output))
"""
output = json.dumps(wMap)
blog_map.write('%s\n' % (output))

raw.close()
email_map.close()
#netID_map.close()
blog_map.close()
