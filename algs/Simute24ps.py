import sys

dp = {}

def calc(inp, length, index, pre):
	global dp

	if index == 0:
		pre_value = inp[0]
	else:
		pre_value = dp[pre]
	
	if index == (length-1) and pre_value == inp[len(inp)-1]:
		print "matching: " + pre
		return
	
	# "+"
	nex = pre + '+'
	dp[nex] = pre_value + inp[index+1]
	calc(inp, length, index+1, nex)

	# "-"
	nex = pre + '-'
	dp[nex] = pre_value - inp[index+1]
	calc(inp, length, index+1, nex)

	last = pre[len(pre)-1]
	# "*"
	nex = pre + '*'
	if last == '*' or last == '/':
		dp[nex] = pre_value * inp[index+1]
	else:
		pre_value = dp[pre[:len(pre)-2]]
		dp[nex] = 
	calc(inp, length, index+1, nex)

	# "+"
	nex = pre + '+'
	dp[nex] = pre_value + inp[index+1]
	calc(inp, length, index+1, nex)


if __name__ == "__main__":
	inp = [1,2,3,4]
	length = len(inp) - 1


