#Letter Writer
#http://www.practice.geeksforgeeks.org/problem-page.php?pid=1339
htable = {}
for i in range(0,15):
    for j in range(0,15):
        hs = i*12 + j*10
        if hs in htable:
            if htable[hs] > i+j:
                htable[hs] = i+j
        else:
            htable[hs] = i+j

T = int(raw_input())
for t in range(T):
    n = int(raw_input())
    if n in htable:
        print htable[n]
    else:
        print -1 
