#Python

a = []
b = []
m = {}
a.append('ejp mysljylc kd kxveddknmc re jsicpdrysi')
a.append('rbcpc ypc rtcsra dkh wyfrepkym veddknkmkrkcd')
a.append('de kr kd eoya kw aej tysr re ujdr lkgc jv')

b.append('our language is impossible to understand')
b.append('there are twenty six factorial possibilities')
b.append('so it is okay if you want to just give up')

m['y'] = 'a'
m['e'] = 'o'
m['q'] = 'z'
m['z'] = 'q'

for i in range(3):
	t1 = a[i]
	t2 = b[i]
	for j in range(len(t1)):
		if t1[j] == ' ':
			continue
		m[t1[j]] = t2[j]

print m

fi = open('/Users/zicheng/Desktop/GCJ/A-small-practice.in', 'r')
n = int(fi.readline())
for i in range(n):
	line = fi.readline().replace('\n','')
	out = ''
	for j in range(len(line)):
		if line[j] == ' ':
			out += ' '
		else:
			out += m[line[j]]
	print 'Case #' + str(i+1) + ': ' + out
