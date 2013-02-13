import math
import random

NUM_MAP_TASKS = 3000
NUM_REDUCE_TASKS = 2

def select(array, order = (len(array)+1)/2):
    pivot = array.pop(random.random()*len(array))
    length = math.floor(len(array)/NUM_MAP_TASKS)
    map_results = {'less than or equal to pivot': [], 'greater than pivot': []}
    for i in range(0, NUM_MAP_TASKS):
        r = map(array[length*i:length*(i+1)], pivot)
        map_results['less than or equal to pivot'] += r['less than or equal to pivot']
        map_results['greater than pivot'] += r['greater than pivot']
        
    # when all map tasks are done
    candidate1 = reduce(map_results['less than or equal to pivot'], math.floor(order), pivot)
    candidate2 = reduce(map_results['greater than pivot', math.ceiling(order - len(map_results['less than or equal to pivot'])-1)], pivot)
    return candidate1 or candidate2
    
def map(array, pivot):
    result = {'less than or equal to pivot': [], 'greater than pivot': []}
    for n in array:
        if n > pivot:
            result['greater than pivot'].append(n)
        else:
            result['less than or equal to pivot'].append(n)
            
    return result

def reduce(array, order, pivot):
    if order == len(array) + 1:
        return pivot
    elif order <= len(array) and order > 0:
        return select(array, order)
    else:
        return None
