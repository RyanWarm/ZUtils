#Python

city_costs = [0]
city_defs = [0]
roads = {}
road_keys = []
destry = {}
min_cost = -1

def handle_input(N, M):
    global city_costs, city_defs, roads, road_keys
    for i in range(N):
        city = (raw_input()).split(' ')
        city_defs.append(city[0])
        city_costs.append(int(city[1]))
    for i in range(M):
    	road = (raw_input()).split(' ')
	road[0] = int(road[0])
	road[1] = int(road[1])
	if city_defs[road[0]] != city_defs[road[1]]:
	    roads[road[0]] = road[1]
	    road_keys.append(road[0])
    return len(roads)

def process_city(city, result):
    global city_costs, destry
    if destry.get(city) and destry[city] == 'y':
    	tmp = result
    else:
    	tmp = result + city_costs[city]
    return tmp

def process(index, result, road_num):
    global city_costs, city_defs, roads, road_keys, destry, min_cost
    #left
    left = road_keys[index]
    tmp = process_city(left, result)
    if index == road_num - 1:
    	if min_cost > tmp or min_cost == -1:
    	    min_cost = tmp
    else:
    	#next level
	destry[left] = 'y'
    	process(index+1, tmp, road_num)
	destry[left] = 'n'
    
    #right
    right = roads[left]
    tmp = process_city(right, result)
    if index == road_num - 1:
    	if min_cost > tmp or min_cost == -1:
    	    min_cost = tmp
    else:
    	#next level
	destry[right] = 'y'
	process(index+1, tmp, road_num)
	destry[right] = 'n'

def clear():
    global city_costs, city_defs, roads, road_keys, destry, min_cost
    del city_costs[1:]
    del city_defs[1:]
    roads.clear()
    del road_keys[:]
    destry.clear()
    min_cost = -1
    
if __name__=="__main__":
	T = int(raw_input())
	result = []
    	for i in range(T):
            val = (raw_input()).split(' ')
            road_num = handle_input(int(val[0]), int(val[1]))
	    if road_num == 0:
	    	result.append(0)
	    else:
	    	process(0, 0, road_num)
	    	result.append(min_cost)
	    clear()
	for i in range(T):
	    print result[i]
