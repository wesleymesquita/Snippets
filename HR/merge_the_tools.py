#https://www.hackerrank.com/challenges/merge-the-tools
s = input()
k = int(input())
c = int(len(s)/k)
for i in range(c):
    ss = s[i*k:i*k+k]
    r = ''
    for ch in ss:
        if ch not in r:
            r = r + ch
    print(r)
