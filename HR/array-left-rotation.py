#https://www.hackerrank.com/challenges/array-left-rotation
def rotate(a,n,d):
    if len(a) == 1 :
        return a
    nr = d%n
    r = a[nr:] + a[0:nr]  
    return r

if __name__=='__main__':
    n,d = input().strip().split()
    n,d = [int(n), int(d)]
    s = input().strip().split()
    r = rotate(s,n,d)
    f  = True
    for c in r:
        if f:
            f = False
        else:
            print(' ', end='')
        print(c, end='')
