# https://www.hackerrank.com/challenges/s10-interquartile-range
# interquartile_range
def median(a):
    midx = int((len(a)-1)/2)
    mval = a[midx]    
    if len(a)%2 == 0:
        mval = (a[midx]+a[midx+1])/2
    return midx, mval
               
if __name__ == "__main__":
    from array import array
    n = int(input())
    V = array('i', [int(d) for d in input().split()]) 
    W = array('i', [int(d) for d in input().split()]) 
    a = array('i')
    for v,w in zip(V,W):
        a.extend([v]*w)
    a = sorted(a)    
    
    midx, mval = median(a)
    if len(a)%2 == 0:
        _, q1val = median(a[:midx+1])
        _, q3val = median(a[midx:])
    else:
        _, q1val = median(a[:midx])
        _, q3val = median(a[midx+1:])
    
    print('{:.1f}'.format(q3val-q1val))    
    