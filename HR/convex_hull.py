#https://www.hackerrank.com/contests/justins-test-contest/challenges/convex-hull-1
# **** NOT WORKING ****
import math
from enum import Enum

class Point:
    def __init__(self, x, y):
        self.x = x 
        self.y = y
    def __lt__(self, pa):
        if self.y < pa.y:
            return True
        elif self.y == pa.y and self.x < pa.x:
            return True
        else:
            return False
    def __str__(self):
        return '({self.x},{self.y})'.format(self=self)  
    
class Vector(Point):
    def __init__(self, pa, pb):
        self.x = pb.x-pa.x 
        self.y = pb.y-pa.y 

class ORI(Enum):
    CCW = 0
    CW  = 1
    COL = 2
    
def orientation(pa, pb, pc):
    ab = Vector(pa, pb)
    ac = Vector(pa, pc)
    v = ab.x*ac.y - ac.x*ab.y
    print('{0}->{1} ({2}) X {3}->{4} {5} == {6}'.format(pa,pb,ab,pa,pc,ac,v))
    if v  0:
        return ORI.CCW
    elif v > 0:
        return ORI.CW
    else:
        return ORI.COL

def dist(pa, pb):
    d = math.sqrt((pa.x-pb.x)**2 + (pa.y-pb.y)**2)
    print('{0}->{1} == {2}'.format(pa, pb, d))
    return d

def norm(v):
    return math.sqrt(v.x*v.x + v.y*v.y)

def angle(pa, pb, pc):
    ab = Vector(pa, pb)
    ac = Vector(pa, pc)
    v = abs(ab.x*ac.y - ac.x*ab.y)
    nab = norm(ab)
    nac = norm(ac)
    a = math.asin(v/(nab*nac))
    return a
    
T = int(input())
for t in range(1, T+1):
    N = int(input())
    p = []
    for i in range(N):
        p.append(Point(*[int(x) for x in input().split()]))
    p = sorted(p)
    p0 = p[0]
    pa = []
    pa.append((p0,0.0))
    pa.append((p[1],0.0))    
    for i in range(1,N-1):
        p1 = p[i]
        p2 = p[i+1]
        a = angle(p0, pa[1][0], p2)
        pa.append((p2,a))    
    pa = sorted(pa, key=lambda p: p[1])  
    
   
    pb = []
    pb.append(pa[0])
    i=1    
    while i <= N-1:
        if i == N-1:
            pb.append(pa[i])            
            i=i+1
        else:
            sa = []
            sa.append(pa[i])
            k = i
            i = i + 1
            while i <= N-1 and pa[i][1] == pa[k][1] :  
                sa.append(pa[i])
                i=i+1
            pt = max(sa, key=lambda x: dist(p0, x[0]) )
            pb.append(pt)                        
    
    for p in pb:
        print('pb:{0} a :{1}'.format(p[0], p[1]))
    
    
    s = []
    s.append(pb[0][0])
    s.append(pb[1][0])
    s.append(pb[2][0])
    
    if len(pb) != 3:    
        if orientation(s[-2], s[-1], s[-3]) != ORI.CCW:
            del s[-1]

        for i in range(3, len(pb)):
            if orientation(s[-1], s[-2], pb[i][0]) == ORI.CCW:
                s.append(pb[i][0])
   
    print('Case #{0}'.format(t))
    for pt in s:
        print('{x} {y}'.format(x=pt.x, y=pt.y))
    
    
    