import sys

def isMatch(filename, pattern, index1, index2):
	print "inside: " + str(index1) + "," + str(index2)
	if pattern[index2] == '?' or filename[index1] == pattern[index2]:
		if index1 == len(filename) - 1 and index2 == len(pattern) - 1:
			return 1
		elif index1 < len(filename) - 1 and index2 < len(pattern) - 1:
			return isMatch(filename, pattern, index1+1, index2+1)
		else:
			return 0

	elif pattern[index2] == '*':
		if index2 == len(pattern) - 1:
			return 1
		while index1 < len(filename):
			if isMatch(filename, pattern, index1, index2+1) == 1:
				return 1
			index1 += 1
	return 0

if __name__ == "__main__":
	s1 = 'index.txt'
	s2 = '*i?de*x?'
	print s1 + '---' + s2
	result = isMatch(s1, s2, 0, 0)
	print "result: " + str(result)
