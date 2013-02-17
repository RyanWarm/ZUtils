import sys

def printSequence(n):
	cur_sum = 0
	result = []
	for i in range(n):
		result.append(-1)
	#for i in range(n):
	doPrint(n, 0, cur_sum, result)

def doPrint(n, index, cur_sum, result):
	#print "cur: " + str(index) + "," + str(cur_sum)
	for i in range(1,n):
		cur_sum += i
		result[index] = i
		if cur_sum == n:
			printResult(result, index)
			return
		if index < n-1:
			doPrint(n, index+1, cur_sum, result)
		cur_sum -= i

def printResult(result, index):
	res = ''
	for i in range(index):
		res += str(result[i]) + ','
	res += str(result[index])
	print res

if __name__ == "__main__":
	n = 5
	printSequence(n)
