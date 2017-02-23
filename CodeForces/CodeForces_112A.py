#http://codeforces.com/problemset/problem/112/A

def str_cmp(a, b):
    sz = len(a)
    if len(b) < sz:
        sz = len(b)
    
    i = 0
    cmp = 0
    while i < sz:
        if ord(a[i]) < ord(b[i]) and cmp == 0:
            return -1
        elif ord(a[i]) > ord(b[i]) and cmp == 0:
            return 1
        i = i + 1
    
    
    if cmp == 0:
        if len(a) > sz:
            return 1
        elif len(b) > sz:
            return -1
    
    return 0

if __name__ == '__main__':
    a = input().lower() 
    b = input().lower()
    
    print(str_cmp(a, b))
    
