import sys

def lcs(s1, s2):
	len1 = len(s1)
	len2 = len(s2)
	tmp = []
	for i in range(len1):
		arr = []
		for j in range(len2):
			arr.append(0)
		tmp.append(arr)
	
	maxLen = 0
	ind_i = 0
	ind_j = 0
	for i in range(1,len1):
		for j in range(1,len2):
			if s1[i] == s2[j]:
				tmp[i][j] = tmp[i-1][j-1] + 1
			if tmp[i][j] > maxLen:
				maxLen = tmp[i][j]
				ind_i = i
				ind_j = j

	print "result: " + str(maxLen) + "--(" + str(ind_i-maxLen+1) + "," + str(ind_j-maxLen+1) + ")" + ":" + s1[ind_i-maxLen+1:ind_i+1]

if __name__ == "__main__":
	s1 = 'ADEDSDEKDOSDSDOFIJLENDDDDDDWLFSDOFLED'
	s2 = 'DEIDLOWEELNDDDDDDDDDDSDKLDSJFOWENLGJSHLDFJ'
	print s1 + ":" + s2
	lcs(s1, s2)
