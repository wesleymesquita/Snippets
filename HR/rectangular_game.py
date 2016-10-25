N = int(input())
x = []
y = []
for n in range(N):
    a,b = [int(x) for x in input().split()]
    x.append(a)
    y.append(b)
x = sorted(x)
y = sorted(y)
print(x[0]*y[0])
 