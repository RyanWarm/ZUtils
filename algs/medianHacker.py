#Python

def getPosition(datas,val,size):
	s = 0
	e = size - 1
	m = 0
	while s < e:
		m = int((s+e)/2)
		if datas[m] < val:
			s = m + 1
		else:
			e = m - 1
	if s == e and datas[s] < val:
		m = s + 1
		
	return m

def insertValue(vals,val,size):
	if val in vals:
		vals.insert(vals.index(val),val)
	else:
		p = getPosition(vals,val,size)
		vals.insert(p,val)
	
if __name__=="__main__":
	N = int(raw_input())
	vals_l = []
	vals_r = []
	size = 0
	ext_val = -1

	for i in range(N):
		cmd = (raw_input()).split(' ')
		val = int(cmd[1])
		if cmd[0] == 'a':
			if ext_val == -1:
				#save corresponding value into ext_val
				if size == 0:
					ext_val = val
				elif val < vals_l[size-1]:
					#insert into left
					ext_val = vals_l[size-1]
					insertValue(vals_l,val,size)
					del vals_l[size]
				elif val > vals_r[0]:
					#insert into right
					ext_val = vals_r[0]
					insertValue(vals_r,val,size)
					del vals_r[0]
				else:
					#save to ext_val directly
					ext_val = val
				print ext_val
			else:
				#save values into correponding parts
				if val > ext_val:
					#save val into vals_r and ext_val into vals_l
					insertValue(vals_r,val,size)
					insertValue(vals_l,ext_val,size)
				else:
					insertValue(vals_r,ext_val,size)
					insertValue(vals_l,val,size)
				ext_val = -1
				size += 1
				tmp = vals_l[size-1]+vals_r[0]
				if tmp % 2 == 0:
					print tmp/2
				else:
					print float(tmp)/2
		else:
			if val == ext_val:
				ext_val = -1
				if size == 0:
					print 'Wrong'
				else:
					tmp = vals_l[size-1]+vals_r[0]
					if tmp % 2 == 0:
						print tmp/2
					else:
						print float(tmp)/2
			elif val in vals_l:
				del vals_l[vals_l.index(val)]
				ext_val = vals_r[0]
				del vals_r[0]
				size -= 1
				print ext_val
			elif val in vals_r:
				del vals_r[vals_r.index(val)]
				ext_val = vals_l[size-1]
				del vals_l[size-1]
				size -= 1
				print ext_val
			else:
				print 'Wrong!'
