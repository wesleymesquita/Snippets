#https://www.hackerrank.com/contests/booking-passions-hacked-backend/challenges/reviews
import datetime
import time

JUNE_2016 = int(time.mktime(datetime.datetime(year=2016, day=15, month=6, hour=0, tzinfo=datetime.timezone.utc).timetuple())) 
JULY_2016 = int(time.mktime(datetime.datetime(year=2016, day=15, month=7, hour=0, tzinfo=datetime.timezone.utc).timetuple())) 

def calc_reviewer_points(rev_body, unix_date):
    rpoints = 0
    lbody = len(rev_body)
    if lbody >= 100:
        rpoints = rpoints + 20
    else:    
        rpoints = rpoints + 10
    if unix_date>=JUNE_2016 and unix_date<JULY_2016:  
        rpoints = rpoints + 20
    else:
        rpoints = rpoints + 10
    return rpoints


class Reviewer:
    def __init__(self, rid, points=0):
        self.rid = rid
        self.points = points
        self.revs = set()
    def __str__(self):
        return str("Reviewer : " + str(self.rid) + " has " + str(self.points) + " points.")

class Passion:
    def __init__(self, name):
        self.name = name
        self.reviewers = {}
    def __str__(self):
        pstr = "(Passion : " + self.name + " Reviewers:\n"
        if len(self.reviewers) > 0:
            for r in self.reviewers:
                pstr = pstr + "\t[" + str(self.reviewers[r]) + "]\n" 
        else:
            pstr += "\tNo Reviewer"
            
        return pstr
    
    
    
if __name__ == "__main__":
    n,m = input().split()
    n = int(n)
    m = int(m)
    P = {}
    POrd = []
    for i in range(n):
        pname = input().lower()
        P[pname] = Passion(pname)
        POrd.append(pname)
    for i in range(m):
        rid, rtimestamp = input().split()
        rid = int(rid)
        rtimestamp = int(rtimestamp)
        rbody = input().lower()       

        lbody = len(rbody)
        rpoints = calc_reviewer_points(rbody,rtimestamp) 
        
        rbody = rbody.split()
        
        rbody = set(rbody)
        for p in P:
            for w in rbody:
                if p in w :  
                    if rid in P[p].reviewers:
                        if  rtimestamp not in P[p].reviewers[rid].revs:
                            P[p].reviewers[rid].points = P[p].reviewers[rid].points + rpoints
                            P[p].reviewers[rid].revs.add(rtimestamp)
                    else:
                        r = Reviewer(rid, rpoints)
                        r.revs.add(rtimestamp)
                        P[p].reviewers[rid] = r
                         
    R = []    
    for p in POrd:
        max_points = -1        
        max_rev_id = -1
        for r in P[p].reviewers: 
            if P[p].reviewers[r].points > max_points:
                max_points = P[p].reviewers[r].points
                max_rev_id = r                
            elif  P[p].reviewers[r].points == max_points and r < max_rev_id:
                max_rev_id = r
        R.append(max_rev_id)   
    for r in R:
        print(r)
    
    
    
    
    
