#Python

def testNext(secret,obs,index):
	nex = (secret * 5402147 + 54321) % 10000001
	if (nex % 1000) == obs[index]:
		if index == len(obs) - 1:
			return True
		else:
			return testNext(nex,obs,index+1)
	else:
		return False
	
if __name__=="__main__":
	#obs = [767,308,284]
	#obs = [862,452,303,558,767,105,911,846,462]
	obs = [23,786,292,615,259,635,540]
	test = obs[0]
	while True:
		if testNext(test,obs,1) == True:
			print test
			break
		test += 1000
