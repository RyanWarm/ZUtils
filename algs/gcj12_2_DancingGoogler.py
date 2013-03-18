#!/usr/local/python
import sys
file_in = sys.argv[1]
fi = open(file_in,'r')
T = int(fi.readline())
for i in range(T):
	vals = (fi.readline()).split(' ')
	N = int(vals[0])
	S = int(vals[1])
	p = int(vals[2])
	result = 0

	for j in range(N):
		val = int(vals[3+j])
		base = val / 3
		rem = val % 3
		if base >= p:
			result += 1
			continue
		
		if base < p - 2:
			continue

		if base == p - 2:
			if S == 0:
				continue
			if rem == 2:
				result += 1
				S -= 1
		else:
			#base == p -1
			if rem > 0:
				result += 1
			elif S > 0 and base > 0:
				result += 1
				S -= 1
	
	print "Case #" + str(i+1) + ": " + str(result)
