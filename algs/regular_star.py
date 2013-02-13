import sys

def isMatch(a1, a2, i1, i2):
	if a1[i1] == '*':
		while i2 < len(a2):
			if i1 == len(a1) - 1 or isMatch(a1, a2, i1+1, i2) == 1:
				if i1 == len(a1) - 1:
					print str(i1) + ':' + a1[i1] + '--' + str(i2) + ':' + a2[i2]
				else:
					print str(i1+1) + ':' + a1[i1+1] + '--' + str(i2) + ':' + a2[i2]
				return 1
			else:
				i2 += 1
	if a2[i2] == '*':
		while i1 < len(a1):
			if i2 == len(a2) - 1 or isMatch(a1, a2, i1, i2+1) == 1:
				if i2 == len(a2) - 1:
					print str(i1) + ':' + a1[i1] + '--' + str(i2) + ':' + a2[i2]
				else:
					print str(i1) + ':' + a1[i1] + '--' + str(i2+1) + ':' + a2[i2+1]
				return 1
			else:
				i1 += 1
	if i1 == len(a1) or i2 == len(a2):
		return 0

	if a1[i1] == a2[i2]:
		if i1 == len(a1) - 1 and i2 == len(a2) - 1:
			print str(i1) + ':' + a1[i1] + '--' + str(i2) + ':' + a2[i2]
			return 1
		else:
			return isMatch(a1, a2, i1+1, i2+1)
	else:
		return 0

if __name__ == '__main__':
	a1 = 'adfiek*kde*daodf'
	a2 = 'a*keadfdk*ado*'
	print a1
	print a2

	match = isMatch(a1, a2, 0, 0)
	print match
