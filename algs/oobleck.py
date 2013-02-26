# python

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

print "d_max=" + str(d_max)
dp = [[0 for col in range(d_max)] for row in range(N+1)]
for i in range(N+1):
    dp[i][0] = 1

base = 1
for i in range(1,d_max):
    print "i=" + str(i)
    base *= M
    print "base=" + str(base)
    tmp_s = 0
    while tmp_s <= N:
    	print "tmp_s=" + str(tmp_s)
        for j in range(tmp_s,N+1):
    	    print "j=" + str(j)
            dp[j][i] += dp[j-tmp_s][i-1]
        tmp_s += base
print dp
print dp[N][d_max-1]
