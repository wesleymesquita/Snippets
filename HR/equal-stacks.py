#https://www.hackerrank.com/challenges/equal-stacks/problem
#!/bin/python3

import os
import sys

#
# Complete the equalStacks function below.
#
def equalStacks(h1, h2, h3):
    s = list(map(sum, [h1, h2, h3]))
    
    s = [[s[0], h1], [s[1], h2], [s[2], h3]]
    s.sort(key=lambda x: x[0], reverse=True)
    
    while s[0][0] != s[1][0] or s[0][0] != s[2][0] or s[1][0] != s[2][0]:
        if s[0][0] > s[1][0]:
            s[0][0] -= s[0][1].pop(0)
        if s[0][0] > s[2][0]:
            s[0][0] -= s[0][1].pop(0)
        if s[1][0] > s[2][0]:
            s[1][0] -= s[1][1].pop(0)
        s.sort(key=lambda x: x[0], reverse=True)
    return  s[0][0]
    
if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    n1N2N3 = input().split()

    n1 = int(n1N2N3[0])

    n2 = int(n1N2N3[1])

    n3 = int(n1N2N3[2])

    h1 = list(map(int, input().rstrip().split()))

    h2 = list(map(int, input().rstrip().split()))

    h3 = list(map(int, input().rstrip().split()))

    result = equalStacks(h1, h2, h3)

    fptr.write(str(result) + '\n')

    fptr.close()

