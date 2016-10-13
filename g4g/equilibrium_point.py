# Geeks for Geeks 
# Equilibrium point
T = int(raw_input())
for t in range(T):
    N = int(raw_input())
    d = raw_input().split()
    if N == 1:
        print("1")
    else: 
        d = [int(x) for x in d]
        s = [d[0]]
        r = [d[-1]]
        for n in range(1,N):
            s.append((s[n-1]+d[n]))
            r.insert(0, (r[0]+d[-1-n]))
    
        eq = -1
        for n in range(0,N):    
            if n==0: 
                if r[1] == 0:
                    eq = 1
                    break
            elif n==N-1:
                if s[N-2] == 0:
                    eq = N
                    break
            else:
                if s[n-1] == r[n+1]:
                    eq = n+1
                    break
        print str(eq)
        
