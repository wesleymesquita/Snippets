#Geeks for Geeks - Faulty Keyboard
#http://www.practice.geeksforgeeks.org/problem-page.php?pid=1375

import math

ms = [None]*(2**16)
t = [None]*(2**14)
t[1]=1
ms[1]=1
log10 = math.log(10)
i = 2
dcount = 1
while dcount < 38890:
    t[i] = t[i-1] + int(len(str(i)))
    ms[t[i]] = i
    dcount = t[i]
    i = i + 1

T =  int(raw_input())

for t in range(T):
    n = int(raw_input())
    while ms[n] == None:
        n = n-1
    print ms[n]

