# Geeks for Geeks - Count Increasing Subsequences
# http://www.practice.geeksforgeeks.org/problem-page.php?pid=1393
T = int(raw_input())
for t in range(0,T):
    N = int(raw_input())
    d = raw_input().split()
    d = [int(x) for x in d]
    a = []
    for i in range(0,N):
        a.append(0)
    a[N-1] = 1
    for i in reversed(range(0,N-1)):
        a[i] = 1
        for j in range(i, N):
            if d[i] < d[j]:
                a[i] = a[i] + a[j]
    
    acc = 0            
    for i in range(0,N):
        acc = acc + a[i]
    print acc
