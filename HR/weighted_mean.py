#https://www.hackerrank.com/challenges/s10-weighted-mean
from array import array
n = int(input())
v = array('i', [int(d) for d in input().split()])
w = array('i', [int(d) for d in input().split()])
f = array('i', [val*wei for val, wei in zip(v,w)])
r = sum(f)/sum(w)
print('{:.1f}'.format(r))
