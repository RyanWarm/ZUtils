import sys

N = int(raw_input())
frequent = {}
revert = {}

for i in range(N):
	s = raw_input()
	count = 0
	if frequent.get(s):
		count = frequent[s]
	count += 1
	frequent[s] = count

for term in frequent:
	count = frequent[term]
	term_l = []
	if revert.get(count):
		term_l = revert[count]
	term_l.append(term)
	revert[count] = term_l

K = int(raw_input())
s = 0

revert_key = sorted(revert.iterkeys(), reverse=True)
for count in revert_key:
	l = sorted(revert[count])
	length = len(l)
	if s + length < K:
		for term in l:
			print term
		s += length
	else:
		# >= K
		left = K - s
		for i in range(left):
			print l[i]
		break
		
