#https://www.hackerrank.com/contests/booking-passions-hacked-backend/challenges/a-couple-and-their-passions

import math

class City:
    def __init__(self, lat, longt, name, passsions):
        self.lat = lat
        self.longt = longt
        self.name = name
        self.passions = passsions
class CPair:
    def __init__(self, city1, city2, npas):
        self.city1 = city1
        self.city2 = city2
        self.npas = npas
        
def deg2rad(deg):
    return (deg*2.0*3.14159265359)/360.0

def dist_bet(city1, city2):
    EARTH_RADIUS = float(6371.0)
    city1_lat = deg2rad(city1.lat)
    city1_long = deg2rad(city1.longt)
    city2_lat = deg2rad(city2.lat)
    city2_long = deg2rad(city2.longt)    
    return math.acos(math.sin(city1_lat)*math.sin(city2_lat) + math.cos(city1_lat)*math.cos(city2_lat)*math.cos(city2_long - city1_long))*EARTH_RADIUS

P = set()
n = int(input())
for i in range(n):
    pdata = input().split()
    m = int(pdata[0])    
    for j in range(m):
        P.add(pdata[1+j])
C = set()
y = int(input())
for j in range(y):
    cdata = input().split()
    cname = cdata[0]
    clat = float(cdata[1])
    clong = float(cdata[2])
    np = int(cdata[3])
    cpas = set()
    for i in range(np):
        if cdata[4+i] in P:
            cpas.add(cdata[4+i])
    c = City(clat, clong, cname, cpas)        
    C.add(c)

C = sorted(C, key=lambda x : len(x.passions), reverse=True)
Pairs = set()
for i in range(len(C)-1):
    for j in range(i+1, len(C)):
        city1 = C[i]
        city2 = C[j]
        n_all_passions = len(city1.passions.union(city2.passions))
        if len(Pairs) == 0 or (len(Pairs) >0 and n_all_passions >= list(Pairs)[-1].npas):
            Pairs.add(CPair(city1, city2, n_all_passions))    
Pairs = sorted(Pairs, key=lambda x : x.npas, reverse=True)
max_pas = Pairs[0].npas
Pairs = [p for p in Pairs if p.npas == max_pas]

if len(Pairs) == 1:
    c1_name = Pairs[0].city1.name
    c2_name = Pairs[0].city2.name
    if c1_name > c2_name:
        c1_name, c2_name = c2_name, c1_name
    print(c1_name + " " + c2_name)
else:      
    FPairs = set()
    for p in Pairs:
        c1 = p.city1
        c2 = p.city2
        d = dist_bet(c1, c2)
        FPairs.add((c1, c2, d))
        
        
    FPairs = sorted(FPairs, key=lambda x : x[2])
    
    c1_name = FPairs[0][0].name
    c2_name = FPairs[0][1].name
    if c1_name > c2_name:
        c1_name, c2_name = c2_name, c1_name

    print(c1_name + " " + c2_name)   


