class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y
    
def orient(pa, pb, pc):
    v1 = (pb.x-pa.x, pb.y-pa.y)
    v2 = (pc.x-pa.x, pc.y-pa.y)
    o = v1[0]*v2[1] - v1[1]*v2[0]
    if o < 0: 
        return -1
    elif o > 0:
        return 1
    else:
        return 0
    
T = int(raw_input())
for t in range(0, T):
    x1,y1,x2,y2 = [int(x) for x in raw_input().split()]
    x3,y3,x4,y4 = [int(x) for x in raw_input().split()]
    
    p1 = Point(x1, y1)
    p2 = Point(x2, y2)
    p3 = Point(x3, y3)
    p4 = Point(x4, y4)
    
    o1 = orient(p1,p2,p3)
    o2 = orient(p1,p2,p4)
    o3 = orient(p3,p4,p1)
    o4 = orient(p3,p4,p2)
    
    if o1 == o3 and o1 == 0:
        s1 = (p1, p2)
        if p1.x > p2.x:
            s1 = (p2, p1)
        s2 = (p3, p4)
        if p3.x > p4.x:
            s2 = (p4, p3)
            
        ps = sorted([s1,s2], key=lambda s : s[0].x)
        endf = ps[0][0].x + (ps[0][1].x-ps[0][0].x)
        if endf >= ps[1][0].x or endf >= ps[1][1].x:
            print 1
        else:
            print 0
    else:
        #print (o1, o2, o3, o4)
        if o1 != o2 and o3 != o4:
            print 1
        else:
            print 0
        