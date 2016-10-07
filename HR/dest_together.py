#https://www.hackerrank.com/contests/booking-passions-hacked-backend/challenges/destinations-together-3

def fac(n):
    if n == 1:
        return 1
    else:
        return n*fac(n-1)
            
n,m,c = input().split()
n =int(n)
m =int(m)
c =int(c)
un = abs(n-c)
um = abs(m-c)
col = un + um + c-1
if col == 0:
    print("1")
else:    
    print(fac(col))

