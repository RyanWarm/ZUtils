#Python
import sys,json
import pdb

def median_for_five(array, start, end):
	tmp = []
	i = start
	while i < end:
		tmp.append(array[i])
		i += 1
	tmp = sorted(tmp)
	print "==tmp: " 
	print tmp
	print "start: " + str(start) + ",end: " + str(end)
	return tmp[len(tmp)/2]

def find_median(array, start, end):
	numOfMedian = int((end-start) / 5)
	medians = []
	for i in range(numOfMedian):
		medians.append(median_for_five(array, start + i*5, start + i*5 + 5))
	medians = sorted(medians)
	print medians
	return medians[numOfMedian/2]

if __name__=="__main__":
	fn = open('int_serials.data','r')
	array = json.loads(fn.readline())
	size = len(array)

	median = find_median(array, 0, size)
	print "got: " + str(median)

	s_array = sorted(array)
	print "expected: " + str(s_array[4999]) + "," + str(s_array[5000])
