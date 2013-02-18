import sys

a = 1000
vals = []

for i in range(a+1):
	vals.append(pow(i,3))

count = 0
for i in range(a-2):
	for j in range(i+3,a+1):
		#print "i: " + str(i) + "," + str(vals[i]) + ",j: " + str(j) + "," + str(vals[j])
		sum_l = vals[i] + vals[j]
		m = i + 1
		n = j - 1
		while m < n:
			#print "m: " + str(m) + "," + str(vals[m]) + ",n: " + str(n) + "," + str(vals[n])
			sum_r = vals[m] + vals[n]
			if sum_r == sum_l:
				print str(i) + "^3 + " + str(j) + "^3 = " + str(m) + "^3 + " + str(n) + "^3"
				count += 1
				m += 1
				n -= 1
			elif sum_r > sum_l:
				n -= 1
			else:
				m += 1

print "total results: " + str(count)
