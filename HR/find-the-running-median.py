#!/bin/python3
"""
https://www.hackerrank.com/challenges/find-the-running-median/problemtgi
Note: Solution based on discussion comments
"""
import os
import sys
import heapq
#
# Complete the runningMedian function below.
#
def runningMedian(a):
    min_heap = []
    max_heap = []
    results = [] 
    for elem in a:
        if len(max_heap) == 0:
            heapq.heappush(max_heap, -elem)
        elif len(min_heap) == 0: 
            heapq.heappush(min_heap, elem)
        else:
            if len(min_heap) == len(max_heap):
                if -max_heap[0] > min_heap[0]:
                    t = -heapq.heappop(max_heap)
                    t2 = heapq.heappop(min_heap)
                    heapq.heappush(min_heap, t)
                    heapq.heappush(max_heap, -t2)
                if elem < -max_heap[0]:
                    heapq.heappush(max_heap, -elem)
                else:
                    heapq.heappush(min_heap, elem)
            elif len(max_heap) > len(min_heap) and elem < -max_heap[0]:
                t = -heapq.heappop(max_heap)
                heapq.heappush(min_heap, t)
                heapq.heappush(max_heap, -elem)
            elif len(max_heap) > len(min_heap) and elem > -max_heap[0]:
                heapq.heappush(min_heap, elem)
            elif len(max_heap) < len(min_heap) and elem < -max_heap[0]:
                heapq.heappush(max_heap, -elem)
            elif len(max_heap) < len(min_heap) and elem > -max_heap[0]:
                t = heapq.heappop(min_heap)
                heapq.heappush(max_heap, -t)
                heapq.heappush(min_heap, elem)
        #print("elem = {} Max = {} Min = {}".format(elem, max_heap, min_heap))
        m = None
        if len(min_heap) == len(max_heap):
            m = (-max_heap[0]+min_heap[0])/2
        elif len(min_heap) > len(max_heap):
            m = min_heap[0] 
        else:
            m = -max_heap[0]
        results.append(float(m))
    return results
        
if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    a_count = int(input())

    a = []

    for _ in range(a_count):
        a_item = int(input())
        a.append(a_item)

    result = runningMedian(a)

    fptr.write('\n'.join(map(str, result)))
    fptr.write('\n')

    fptr.close()

