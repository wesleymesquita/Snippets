from array import array
def median(a):
    midx = int((len(a)-1)/2)
    mval = a[midx]
    if len(a)%2 == 0:
        mval = (a[midx] + a[midx+1])/2 
    return int(midx), int(mval)

if __name__ == "__main__":
    n = int(input())
    a = sorted(array('i', [int(d) for d in input().split()]))
    midx, mval = median(a)
    if len(a)%2 == 0:
        _, q1val = median(a[:midx+1])
        print('{0}'.format(q1val))  
        print('{0}'.format(mval))     
        _, q2val = median(a[midx+1:])
        print('{0}'.format(q2val))          
    else:
        _, q1val = median(a[:midx])
        print('{0}'.format(q1val))
        print('{0}'.format(mval))     
        _, q2val = median(a[midx+1:])
        print('{0}'.format(q2val))
    
    