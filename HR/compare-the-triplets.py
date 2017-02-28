#https://www.hackerrank.com/challenges/compare-the-triplets
#!/bin/python3

import sys


a0,a1,a2 = input().strip().split(' ')
a = [int(a0),int(a1),int(a2)]
b0,b1,b2 = input().strip().split(' ')
b = [int(b0),int(b1),int(b2)]

pa = 0
pb = 0

for e in zip(a,b):
    if e[0] > e[1]:
        pa = pa + 1
    elif e[0] < e[1]:
        pb = pb + 1
print(pa, pb)
        
