# https://www.hackerrank.com/challenges/happy-ladybugs
#!/bin/python3

import sys


Q = int(input().strip())
for a0 in range(Q):
    n = int(input().strip())
    b = input().strip()

    is_happy = True    
    
    if n == 1 and b[0] != '_':
        print('NO')
        continue
    
    if n > 1:    
        if b[0] != b[1] or b[-1] != b[-2]:
            is_happy = False

    if is_happy:
        i = 1
        while i < n-1:        
            if b[i-1] == b[i] or b[i]==b[i+1]: 
                i = i + 1
            else:
                is_happy = False             
                break         

    if not is_happy:
        is_happy = True
        found_space = False    
        
        cbugs = {}
        for c in b:
            if c == '_':
                found_space = True
            else:
                if c not in cbugs:
                    cbugs[c]=1
                else:
                    cbugs[c] = cbugs[c] + 1
        if not found_space:
            is_happy = False
        else:
            for c in cbugs:                
                if cbugs[c]==1:
                    is_happy = False
                    break        
    if is_happy:
        print('YES')
    else:
        print('NO')
                    
        
