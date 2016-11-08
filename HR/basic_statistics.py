# https://www.hackerrank.com/challenges/s10-basic-statistics 
from  array import array
n = int(input())
a = array('d', [float(d) for d in input().split()])
av = sum(a)/n
print('{:.1f}'.format(av))
md = sorted(a)
m = int((len(md)-1)/2)
print('{:.1f}'.format( (md[m] + md[m+1])/2))
mode = -1
i = 0
mode_cnt = -1
mode_val = -1

while i < n:
    c_mode_cnt = 1
    c_mode_val = md[i] 
    i = i + 1  
    while i < n and md[i] == c_mode_val:
        c_mode_cnt = c_mode_cnt + 1
        i=i+1
    if c_mode_cnt > mode_cnt:
        mode_cnt = c_mode_cnt
        mode_val = c_mode_val
print('{0}'.format(int(mode_val)))