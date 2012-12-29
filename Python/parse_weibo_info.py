#encoding=utf8
import sys,json

raw = open('/zdisk/data/raw/alignment/weibo.mail', 'r')
email_map = open('./data/email_weiboID.data', 'w')
weiboID_map = open('./data/weiboID_zid.data', 'w')
zid_map = open('./data/zid_map.data', 'w')

result = {}
"""
line = zid_map.readLine()
if line:
	result = json.loads(line)
"""

index = 0
eMap = {}
wMap = {}
zMap = {}

for line in raw:
	tmp = line.split('\t')
	if tmp and len(tmp) == 2:
		weiboID = tmp[0]
		info = json.loads(tmp[1])
	
		#email_map process
		if info.get('QQ'):
			eMap[info['QQ']+'.qq.com'] = weiboID
		if info.get('邮箱'):
			eMap[info['邮箱']] = weiboID
		if info.get('MSN'):
			eMap[info['MSN']] = weiboID
		
		#weiboID_map process
		wMap[weiboID] = index

		#zid_map process
		idSet = {}
		idSet['weibo'] = weiboID
		zMap[index] = idSet

		index += 1

"""
for i in range(10):
        tmp = {}
        tmp['zid'] = 'z' + str(i)
        result[i] = tmp
"""

output = json.dumps(eMap)
email_map.write('%s\n' % (output))

output = json.dumps(wMap)
weiboID_map.write('%s\n' % (output))

output = json.dumps(zMap)
zid_map.write('%s\n' % (output))

raw.close()
email_map.close()
weiboID_map.close()
zid_map.close()
