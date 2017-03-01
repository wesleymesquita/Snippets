#https://www.hackerrank.com/challenges/designer-pdf-viewer
#!/bin/python3

import sys


h = list(map(int, input().strip().split(' ')))
word = input().strip() add 

lh = {}
i = 0
while i < len(h):
    lh[ chr(ord('a')+i) ] = h[i]    
    i = i + 1

maxH = -1
for c in word:
    if lh[c] > maxH:
        maxH=lh[c]

print(len(word)*maxH)    

