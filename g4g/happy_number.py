#code
T = int(raw_input())
for t in range(0,T):
    n = [c for c in raw_input() if c.isdigit()]
    end = False
    while not end:
        s = sum([int(p)**2 for p in n if p != ''])
        if s == 1:
            print 1
            end = True
            continue
        nxt = "".join([d for d in str(s)])    
        if len(nxt) == 1:
            print 0
            end = True
            continue
        else:
            n = nxt