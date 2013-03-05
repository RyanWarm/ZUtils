# python

rem = int(raw_input())

bit = 1
pre = 0
nxt = 10
cap = nxt - pre

while rem > cap:
	rem -= cap
	pre = nxt
	nxt *= 10
	bit += 1
	cap = (nxt - pre) * bit

#inside current bits
a = int(rem / bit) + pre
b = rem % bit
res = a
while b > 0:
	res = res % pow(10,bit-1)
	b -=1
	bit -=1
res = int(res / pow(10,bit-1))
print res
