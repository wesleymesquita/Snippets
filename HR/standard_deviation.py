#https://www.hackerrank.com/challenges/s10-standard-deviation
from array import array
import math
n = int(input())
V = array('i', [int(d) for d in input().split()])
u = sum(V)/n
s = 0.0
for v in V:
    s = s + (v-u)*(v-u)
s = math.sqrt(s/n)
print('{:.1f}'.format(s))