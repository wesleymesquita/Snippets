#https://www.hackerrank.com/challenges/s10-poisson-distribution-2
def x_sq(l):
    return l + l**2
la, lb = [float(x) for x in input().split()]

a = 160 + 40*x_sq(la)
b = 128 + 40*x_sq(lb)

print('{:.3f}'.format(a))
print('{:.3f}'.format(b))