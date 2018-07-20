#https://www.hackerrank.com/challenges/balanced-brackets/problem
#Accepted, no consult to discussion

#!/bin/python3

import math
import os
import random
import re
import sys

# Complete the isBalanced function below.
def isBalanced(s):
    if len(s)%2 == 1:
        return "NO"
    if s[0] in [']', '}',']']:
        return "NO"
    stack = []

    for c in s:
        if c in ['(', '{', '[']:
            stack.append(c)
        else:
            if len(stack) == 0:
                return "NO"
            if c == ')' and stack[-1] != '(':
                return "NO"
            elif c == ']' and stack[-1] != '[':
                return "NO"
            elif c == '}' and stack[-1] != '{':
                return "NO"
            else:
                stack.pop()
    if len(stack) != 0:
        return "NO"
    return "YES"
if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    t = int(input())

    for t_itr in range(t):
        s = input()

        result = isBalanced(s)

        fptr.write(result + '\n')

    fptr.close()

