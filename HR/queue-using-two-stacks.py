# https://www.hackerrank.com/challenges/queue-using-two-stacks/problem
# Note : I did check dicussion forum before submit. Also, it is horrible to use `global', however, it is easy to fix.

from array import array
s = [array('i',[0]*(10**5+1)),array('i',[0]*(10**5+1))]
enq_pt, deq_pt = 0, 1
enq_off, deq_off = -1, -1


def enq(val):
    global enq_off, deq_off
    enq_off += 1
    s[enq_pt][enq_off] = val

def deq():
    global enq_off, deq_off
    if deq_off == -1:
        while enq_off >=0:
            deq_off += 1
            s[deq_pt][deq_off] = s[enq_pt][enq_off]
            enq_off -= 1
    deq_off-=1

def printq():
    global enq_off, deq_off
    if deq_off >= 0:
        return print(s[deq_pt][deq_off])
    print(s[enq_pt][0])
    
nq = int(input())
for _ in range(nq):
    c = list(map(int, input().rstrip().split()))
    if c[0] == 1:
        enq(c[1])
    elif c[0] == 2:
        deq()
    else:
        printq()
