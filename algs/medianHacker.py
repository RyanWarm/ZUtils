#Python

def getPosition(datas,val,size):
	s = 0
	e = size - 1
	while s <= e:
		m = int((s+e)/2)
		if datas[m] < val:
			s = m + 1
		else:
			e = m - 1
	return m

if __name__=="__main__":
	N = int(raw_input())
	vals_l = []
	vals_r = []
	dic_l = {}
	dic_r = {}
	size_l = 0
	size_r = 0
	ext_val = 0

	for i in range(N):
		cmd = (raw_input()).split(' ')
		val = int(cmd[1])
		if cmd[0] == 'a':
			if size_l == size_r:
				if size_l == 0:
					ext_val = val
				else if val < vals_l[size_l-1]:
					#insert into left
					ext_val = vals_l[size_l-1]
					if dic_l.has_key(val):
						vals_l.insert(dic_l[val]+1,val)
						dic_l[val] += 1
					else:
						p = getPosition(vals_l,val,size_l)
						if vals_l[p] < val:
							p += 1
						vals_l.insert(p,val)
					del vals_1[size_l]
		else:
