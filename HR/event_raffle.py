#https://www.hackerrank.com/contests/booking-passions-hacked-backend/challenges/lottery-ii/
# Note : it is still failing on case test #8 . I tried an ad-hoc solution in 'why-not' mode
# need to look for a decent soltution....

class Person:
    def __init__(self, pid, passions):
        self.pid = pid
        self.passions = passions
        self.evts = set()
        
class Passion:
    def __init__(self, pid):
        self.pid = pid
        self.evts = set()        
    def add_evt(self, eid):
        self.evts.add(eid)

class Event:
    def __init__(self, eid):
        self.eid = eid
        self.available = True
        self.passions = set()
        
n = int(input())
People = {}
Passions = {}
Events = {}

for i in range(n):
    pdata = input().split()
    np = int(pdata[1])
    ppassions = set()
    for j in range(np):
        ppassions.add(pdata[2+j])
    p = Person(i+1, ppassions)
    People[p.pid] = p

for i in range(n):
    edata = input().split()
    np = int(edata[0])
    eid = i + 1
    e = Event(eid)
    Events[eid] = e
    
    for j in range(np):        
        pid = edata[1+j]
        e.passions.add(pid)
        if pid in Passions:
            Passions[pid].add_evt(eid)
        else:
            p = Passion(pid)
            p.add_evt(eid)
            Passions[pid] = p

for p in People:
    for passion in People[p].passions:
        if passion in Passions:
            People[p].evts = People[p].evts.union(Passions[passion].evts)
    People[p].evts = list(People[p].evts)
    People[p].evts = sorted(People[p].evts, key=lambda e : len(Events[e].passions))

People = list(People.values())
People = sorted(People, key=lambda p : len(p.evts))
countp = 0

for p in People:
    for e in p.evts:
        if Events[e].available:
            #print("P " + str(p.pid) + " E =="  + str( Events[e].eid) )
            Events[e].available = False
            countp = countp + 1
            break
print(countp)            


