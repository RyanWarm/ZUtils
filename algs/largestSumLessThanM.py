# python

dp = []
ex = []
N = -1
K_L = -1
M_L = -1
result = -1

def process(vals,n,k,m):
    global dp,ex,result,K_L,M_L
    if n == k:
    	if ex[n-1] < m:
    	    dp[n-1][k-1][m-1] = ex[n-1]
	else:
	    dp[n-1][k-1][m-1] = 0
    	return dp[n-1][k-1][m-1]
    if dp[n-1][k-1][m-1] != -1:
    	return dp[n-1][k-1][m-1]
    tmp1 = process(vals,n-1,k,m)
    if m > int(vals[n-1]):
    	if k == 1:
	    tmp2 = int(vals[n-1])
	else:
    	    tmp2 = process(vals,n-1,k-1,m-int(vals[n-1])) + int(vals[n-1])
    else:
    	tmp2 = 0
    if tmp1 >= M_L:
    	tmp1 = 0
    if tmp2 >= M_L:
    	tmp2 = 0
    if tmp1 > tmp2:
    	dp[n-1][k-1][m-1] = tmp1
    else:
    	dp[n-1][k-1][m-1] = tmp2
    if k == K_L and dp[n-1][k-1][m-1] > result:
    	print "modify: " + str(n-1) + "," + str(k-1) + "," + str(m-1)
    	result = dp[n-1][k-1][m-1]
    return dp[n-1][k-1][m-1]

if __name__=="__main__":
    vals = (raw_input()).split(' ')
    N = int(vals[0])
    K_L = int(vals[1])
    M_L = int(vals[2])
    vals = (raw_input()).split(' ')
    dp = [[[-1 for m in range(M_L)] for k in range(K_L)] for n in range(N)]
    print dp
    ex.append(int(vals[0]))
    for i in range(1,K_L):
    	ex.append(ex[i-1] + int(vals[i]))
    print ex
    process(vals,N,K_L,M_L)
    print result
