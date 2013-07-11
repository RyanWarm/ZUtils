#!/usr/local/python
import sys

def get_char(value):
	A = ord('A') - 1
	B = A + value
	return chr(B)

inp = sys.argv[1]
dp = []
for i in range(len(inp)):
	dp.append([])
	if i == 0:
		dp[i].append(get_char(int(inp[i])))
	else:
		cur = get_char(int(inp[i]))
		for r in dp[i-1]:
			dp[i].append(r+cur)
		test = int(inp[i-1:i+1])
		if test < 26:
			cur = get_char(test)
			if i == 1:
				dp[i].append(cur)
			else:
				for r in dp[i-2]:
					dp[i].append(r+cur)

print dp[len(inp)-1]
