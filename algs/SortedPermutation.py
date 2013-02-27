# Python

def permute(vals,index,used,result):
	p = 0
	if index == len(vals) - 1:
		p = 1
		rs = ''
		for i in range(index):
			rs += result[i]
	for i in range(len(vals)):
		if used[i] == 1:
			continue
		if p == 1:
			rs += vals[i]
			print rs
		else:
			result[index] = vals[i]
			used[i] = 1
			permute(vals,index+1,used,result)
			used[i] = 0
	
if __name__=="__main__":
	vals = (raw_input()).split(' ')
	vals = sorted(vals,reverse=True)
	result = ['' for i in range(len(vals))]
	used = [0 for i in range(len(vals))]
	permute(vals,0,used,result)
