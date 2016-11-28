def fac(n):
    if n == 0 or n == 1:
        return 1
    else:
        return n*fac(n-1)

def comb(n, m):
    return fac(n)/(fac(n-m)*fac(m))

a, b = [int(n) for n in input().split()]
n = int(input())

p = 0
for i in range(0,n):
    p = p + ((1-a/b)**(i))*(a/b)

print("{:.3f}".format(p))
    
    