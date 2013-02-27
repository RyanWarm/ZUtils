# python
dp = []
N = -1
M = -1

def process(n,m):
    global dp,N,M
    if dp[n][m] != 0:
    	print "=====match=======:" + str(n) + "," + str(m)
        return dp[n][m]
    base = pow(M,m)
    k = m
    tmp_r = 0
    while k > 0:
	print "base: " + str(base)
        tmp_s = base
        while tmp_s <= n:
    	    print "process: " + str(n-tmp_s) + "," + str(k-1)
            tmp_r += process(n-tmp_s,k-1)
            tmp_s += base
	base /= M
	k -= 1
    dp[n][m] = tmp_r + 1
    print dp
    return dp[n][m]
        
            
if __name__=="__main__":
    inp = (raw_input()).split(' ')
    N = int(inp[0])
    M = int(inp[1])

    d_max = 1
    tmp = M
    while 1:
        if tmp > N:
            break
        else:
            tmp *= M
            d_max +=1

    dp = [[0 for col in range(d_max)] for row in range(N+1)]
    for i in range(N+1):
        dp[i][0] = 1

    result = process(N,d_max-1)
    print result
        
