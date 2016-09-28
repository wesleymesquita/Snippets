#https://www.hackerrank.com/challenges/python-sort-sort/
m, n= input().split()
n = int(n)
m = int(m)
v = []
for i in range(m):
    v.append([])
for j in range(n):
    vals = input().split()
    vals = [int(a) for a in vals]
    for j in range(m):
        v[j].append(vals[j])
col = int(input())
to_sort_col = []
for i in range(n):
    to_sort_col.append((v[col][i], i))
to_sort_col = sorted(to_sort_col, key=lambda x : x[0])
for elem in to_sort_col:
    val,idx = elem
    for i in range(m):
        print(str(v[i][idx]) + " ",end="")
    print("")
