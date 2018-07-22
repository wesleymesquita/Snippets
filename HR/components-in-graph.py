# https://www.hackerrank.com/challenges/components-in-graph/problem
# Note : I have not checked discussion
#!/bin/python3

import os
import sys

from collections import deque

class Node:
    val = -1
    color = 0 #0 - white, 2 -black
    adj = [] 
    def __init__(self, val):
        self.val = val
        self.adj = []
        
def bfs(g, n):
    q = deque() 
    q.append(n)
    count = 1
    while len(q) > 0:
        visiting = q.popleft()
        for v in g[visiting].adj:
            if g[v].color == 0:
                q.append(v)
                count += 1
                print("Added {} from {} ".format(v,n))
                g[v].color = 1
        g[visiting].color = 2
    return count 

#
# Complete the componentsInGraph function below.
#
def componentsInGraph(gb):
    nodes = {}
    for n in gb:
        if n[0] not in nodes:
            nodes[n[0]] = Node(n[0])
        if n[1] not in nodes:
            nodes[n[1]] = Node(n[1])
        nodes[n[0]].adj.append(n[1])
        nodes[n[1]].adj.append(n[0])
        
    comps = []
    for n in nodes:
        if nodes[n].color == 0:
            comps.append(bfs(nodes, n))
    comps.sort()         
    
    return comps[0], comps[-1]   
            
    
if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    n = int(input())

    gb = []

    for _ in range(n):
        gb.append(list(map(int, input().rstrip().split())))

    result = componentsInGraph(gb)

    fptr.write(' '.join(map(str, result)))
    fptr.write('\n')

    fptr.close()
