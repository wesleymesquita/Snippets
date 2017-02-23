def diff_stones():
    n = int(input())
    s = [c for c in input()]
    i =0
    c = 0
    while i<n-1:
        if s[i] == s[i+1] and s[i] != '.':
            s[i] = '.'
            c = c + 1
        i = i+1
    return c

if __name__ == '__main__':
    print(diff_stones())
