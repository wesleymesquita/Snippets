#https://www.hackerrank.com/challenges/s10-poisson-distribution-1
import math

def fac(n):
    if n == 0 or n == 1:
        return 1
    else:
        return n*fac(n-1)

def poisson(l,k):
    p = (l**k * math.exp(-l))/fac(k)
    return p
    
l = float(input())
k = int(input())

print('{:.3f}'.format(poisson(l,k)))
