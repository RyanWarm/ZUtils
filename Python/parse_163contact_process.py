#encoding=utf8
import sys,json,string,chardet

reload(sys)
sys.setdefaultencoding('utf8')
raw = open('/zdisk/data/raw/alignment/user_contact.163', 'r')
email_weibo = open('./data/email_weiboID.data', 'r')
weibo_zid = open('./data/weiboID_zid.data', 'r')
netID_map = open('./data/163ID_zid.data', 'w')
zid_map = open('./data/zid_map.data', 'r')
zid_map_163 = open('./data/zid_map_2_163.data', 'w')

result = {}

line = zid_map.readline()
if line:
	result = json.loads(line)

index = 2633290

eMap = {}
line = email_weibo.readline()
if line:
	eMap = json.loads(line)

wMap = {}
line = weibo_zid.readline()
if line:
	wMap = json.loads(line)

nMap = {}

mappedCount = 0

#i = 0
for line in raw:
	matched = 0
	tmp = line.split('\t')
	if tmp and len(tmp) == 4:
		netID = tmp[0]
		qq = tmp[1]
		blog = tmp[2]
		email = tmp[3]
		
		mapping = {}
		zid = index
		#qq process
		if qq and qq.isdigit():
			qqMail = qq + '.qq.com'
#			print qqMail + '|qq'	
			if eMap.get(qqMail):
#				print "matching: " + qqMail
				weibo_id = eMap[qqMail]
				zid = wMap[weibo_id]
				mapping = result[str(zid)]
				matched = 1
				mappedCount += 1

		if matched == 0 and email and len(email) > 1:
			if string.rfind(email, '\n') == len(email) - 1:
				email = email[:len(email)-1]
#			print email + '|email'
			if eMap.get(email):
#				print "matching: " + email
				weibo_id = eMap[email]
				zid = wMap[weibo_id]
				mapping = result[str(zid)]
				matched = 1
				mappedCount += 1
		
		dot = '.'
		com = '.com'
		cn = '.cn'
		org = '.org'
		if matched == 0 and blog and dot in blog and len(blog) > 15 and len(blog) < 50 and (com in blog or cn in blog or org in blog):
			start = string.find(blog, 'http://')
			if start != -1:
				blog = blog[start+7:]
			end = string.rfind(blog, '/')
			if end == len(blog) - 1:
				blog = blog[:len(blog)-1]
			encoding = chardet.detect(blog)
			if encoding['encoding'] == 'gbk' or encoding['encoding'] == 'utf-8' or encoding['encoding'] == 'ascii':
				wid = ''
				if 'weibo.com/u' in blog:
					start = string.find(blog, 'weibo.com/u')
					blog = blog[start+12:]
					start = string.find(blog, '/')
					if start == -1:
						start = len(blog)
					wid = blog[:start]
				elif 'weibo.com' in blog:
					start = string.find(blog, 'weibo.com')
                                        blog = blog[start+10:]
                                        start = string.find(blog, '/')
                                        if start == -1:
                                                start = len(blog)
                                        wid = blog[:start]
				if len(wid) != 0 and wMap.get(wid):
					print "matching weibo: " + wid
					zid = wMap[wid]
					mapping = result[str(zid)]
					matched = 1
					mappedCount += 1
		
		mapping['163'] = netID
		result[zid] = mapping
		nMap[netID] = str(zid)
		if matched == 0:
			index += 1
#		print "processed: " + str(zid)

"""		
		i += 1
		if i == 1000:
			break
"""
print "Next Index: " + str(index) + "\n"
print "Matched count: " + str(mappedCount) + "\n"

zid_map.close()
output = json.dumps(nMap)
netID_map.write('%s\n' % (output))
"""
output = json.dumps(wMap)
netID_map.write('%s\n' % (output))
"""
output = json.dumps(result)
zid_map_163.write('%s\n' % (output))

raw.close()
email_weibo.close()
netID_map.close()
zid_map.close()
zid_map_163.close()

