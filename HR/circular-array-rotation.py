#https://www.hackerrank.com/challenges/circular-array-rotation
'''
0 1 2 3 4 5

1 - 5  1 2 3 4
2 - 4 5  1 2 3
3 - 3 4 5  1 2
4 - 2 3 4 5  1
5 - 1 2 3 4 5
'''

#!/bin/python3

import sys


n,k,q = input().strip().split(' ')
n,k,q = [int(n),int(k),int(q)]
a = [int(a_temp) for a_temp in input().strip().split(' ')]

k = k%n
if k != 0:
    b = a[(-1)*k:]
    [b.append(e) for e in a[0:(-1)*k]]
    a = b

for a0 in range(q):
    m = int(input().strip())
    print(a[m])
    
