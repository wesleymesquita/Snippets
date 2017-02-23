#http://codeforces.com/problemset/problem/116/A
def tram_line():
    n = int(input())
    i = 0
    cap = 0
    min_cap = 0
    while i<n:
        l , e = [int(n) for n in input().split()]
        cap = cap + e
        cap = cap - l
        if cap > min_cap : 
            min_cap = cap
        i = i + 1
    return min_cap

if __name__ == '__main__':
    print(tram_line())
