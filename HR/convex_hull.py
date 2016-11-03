#https://www.hackerrank.com/contests/justins-test-contest/challenges/convex-hull-1
#**WORKING PARTIALLY. ALGO SEEMS GOOD, BUT FACING PRECISION PROBLEMS**
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
    bc = Vector(pb, pc)
    v = ab.x*bc.y - bc.x*ab.y
    if v == 0:
        return ORI.COL
    elif v<0:
        return ORI.CW
    elif v>0:
        return ORI.CCW
    
def dist(pa, pb):
    d = math.sqrt((pa.x-pb.x)**2 + (pa.y-pb.y)**2)
    #print('dist : {0}->{1} == {2}'.format(pa, pb, d))
    return d

def norm(v):
    return math.sqrt(v.x*v.x + v.y*v.y)

def angle(pa, pb, pc):
    ab = Vector(Point(pb.x, 0), pa)
    ac = Vector(pc, pa)
    v = ab.x*ac.y - ac.x*ab.y
    nab = norm(ab)
    nac = norm(ac)
    a = 0
    if not (nab ==0 or nac == 0):
        a = math.asin(v/(nab*nac))
        if a < 0.0:
            a = a + 3.14159
    elif nab == 0 or nac == 0:
        a = math.asin(1)
    return round(a,1)
    #return round((a*360.0)/(2.0*math.pi))
    
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
    for i in range(1,N):
        pn = p[i]
        a = angle(p0, Point(pn.x, 0), pn)
        pa.append((pn,a))    
    pa = sorted(pa, key=lambda p: p[1])  
 
    #for p in pa:
    #    print('pa:{0} a :{1}'.format(p[0], p[1]))
 
   
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
            pt = sa[0]
            if len(sa) > 1:      
                pt = max(sa, key=lambda x: dist(p0, x[0]) )
            pb.append(pt)                  
    
    
    
    s = []
    s.append(pb[0][0])
    s.append(pb[1][0])
    s.append(pb[2][0])
    
    i = 3
    while i<len(pb):
        #for pt in s:
            #print('\t {i} :: {x} {y}'.format(i=i,x=pt.x, y=pt.y))        
        if len(s) >= 2 and orientation(s[-2], s[-1], pb[i][0]) != ORI.CCW:
            #print('Reject : {0}'.format(s[-1]))
            s.pop()
        #print('Accept : {0}'.format(pb[i][0]))
        s.append(pb[i][0])
        i = i + 1
    
    if len(s) >= 2 and orientation(s[-2], s[-1], s[0]) != ORI.CCW:
        #print('Reject : {0}'.format(s[-1]))
        s.pop()
    
    min_x = min(s, key=lambda p: p.x)
    min_idx = s.index(sorted([p for p in s if p.x == min_x.x], key=lambda p : p.y)[0])
    
    print('Case #{0}'.format(t))
    
    i = min_idx
    c = 0
    while c < len(s):
        print('{x} {y}'.format(x=s[i].x, y=s[i].y))
        c = c + 1
        if i == len(s) -1:
            i = 0
        else:
            i = i + 1
            
                
