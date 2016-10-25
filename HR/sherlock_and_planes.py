class Point:
    def __init__(self, x,y,z):
        self.x = x
        self.y = y
        self.z = z

class Vector(Point):
    pass
        
        
def cross_prod(u, v):
    return Vector(u.y*v.z - u.z*v.y, u.z*v.x - v.z*u.x, u.x*v.y-u.y*v.x)
 
def dot_prod(u,v):
    return u.x*v.x + u.y*v.y + u.z*v.z

T = int(input())
for t in range(T):
    p = Point(*[int(i) for i in input().split()])
    q = Point(*[int(i) for i in input().split()])
    r = Point(*[int(i) for i in input().split()])
    s = Point(*[int(i) for i in input().split()])
    pq = Vector(q.x-p.x, q.y-p.y, q.z-p.z)
    pr = Vector(r.x-p.x, r.y-p. y, r.z-p.z)
    N = cross_prod(pq, pr)
    
    if dot_prod(N,p) == dot_prod(N,s):
        print('YES')
    else:
        print('NO')
     
    