import sys

a = 1000
vals = []

for i in range(a+1):
	vals.append(pow(i,3))

val_map = {}
count = 0
for i in range(a):
	for j in range(i+1,a+1):
		#print "i: " + str(i) + ",j: " + str(j)
		tmp_sum = vals[i] + vals[j]
		if val_map.get(tmp_sum):
			ind = val_map[tmp_sum].split(',')
			print str(i) + "^3 + " + str(j) + "^3 = " + str(ind[0]) + "^3 + " + str(ind[1]) + "^3"
			count += 1
		val_map[tmp_sum] = str(i) + ',' + str(j)

print "total results: " + str(count)

