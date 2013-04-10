#Python

def doPermute(vals, used, index, result, rep):
	#print used
	#print str(index) + "," + str(result) + "," + rep
	if index == 4:
		if result == 24:
			print "====Result: " + rep
		return

	for i in range(4):
		if used[i] == 1:
			continue
		tmp = vals[i]
		used[i] = 1
		
		if index == 0:
			doPermute(vals, used, index+1, tmp, str(tmp))
		else:
			doPermute(vals, used, index+1, result+tmp, rep+"+"+str(tmp))
			doPermute(vals, used, index+1, result-tmp, rep+"-"+str(tmp))
			doPermute(vals, used, index+1, result*tmp, rep+"*"+str(tmp))
			doPermute(vals, used, index+1, result/tmp, rep+"/"+str(tmp))
			
		used[i] = 0

if __name__=="__main__":
	vals = [2,3,4,5]
	used = [0,0,0,0]
	index = 0
	rep = ''
	print vals
	doPermute(vals, used, index, 0, rep)
