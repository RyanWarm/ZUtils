import sys

dp = {}

def calc(inp, length, index, pre):
	global dp
	pre_value = dp[pre]
	
	if index == (length-1):
		if pre_value == inp[len(inp)-1]:
			result = str(inp[0])
			for i in range(1,length):
				result += pre[i] + str(inp[i])
			print "matching: " + result + "=" + str(inp[length])
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
	if last == '*' or last == '/' or last == '$':
		len_pre = len(pre)
		if len_pre <= 2:
			dp[nex] = pre_value * inp[index+1]
		else:
			tmp = len(pre) - 2
			while pre[tmp] == '*' or pre[tmp] == '/':
				tmp -= 1
			if tmp == 0:
				dp[nex] = pre_value * inp[index+1]
			else:
				if pre[tmp] == '+':
					dp[nex] = dp[pre[:tmp]] + (dp[pre[:len(pre)]] - dp[pre[:tmp]]) * inp[index+1]
				else:
					# '-'
					#print str(tmp) + ',' + nex + ',' + pre[:tmp] + ',' + pre[:len(pre)]
					dp[nex] = dp[pre[:tmp]] - (dp[pre[:tmp]] - dp[pre[:len(pre)]]) * inp[index+1]
	else:
		pre_value = dp[pre[:len(pre)-1]]
		if last == '+':
			dp[nex] = pre_value + inp[index] * inp[index+1]
		else:
			dp[nex] = pre_value - inp[index] * inp[index+1]
	calc(inp, length, index+1, nex)

	# "/"
	if inp[index+1] == 0:
		return
	nex = pre + '/'
	if last == '*' or last == '/' or last == '$':
		len_pre = len(pre)
		if len_pre <= 2:
			dp[nex] = pre_value / inp[index+1]
		else:
			tmp = len(pre) - 2
			while pre[tmp] == '*' or pre[tmp] == '/':
				tmp -= 1
			if tmp == 0:
				dp[nex] = pre_value / inp[index+1]
			else:
				if pre[tmp] == '+':
					dp[nex] = dp[pre[:tmp]] + (dp[pre[:len(pre)]] - dp[pre[:tmp]]) / inp[index+1]
				else:
					# '-'
					dp[nex] = dp[pre[:tmp]] - (dp[pre[:tmp]] - dp[pre[:len(pre)]]) / inp[index+1]
	else:
		pre_value = dp[pre[:len(pre)-1]]
		if last == '+':
			dp[nex] = pre_value + inp[index] / inp[index+1]
		else:
			dp[nex] = pre_value - inp[index] / inp[index+1]
	calc(inp, length, index+1, nex)

if __name__ == "__main__":
	inp = [2,10,3,14,5,87]
	length = len(inp) - 1
	pre = '$'
	dp[pre] = inp[0]
	calc(inp, length, 0, pre)

