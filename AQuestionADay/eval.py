#https://www.careercup.com/question?id=5730509222051840
#amazon-interview-questions

#Given an arithmetic expression, write a program to find the value of the expression. Only binary operations that are allowed are +,-,*,/. Also assume that all parentheses are well matched.

#Note that the use of eval() is forbidden

#Input format :There is a single positive integer T on the first line of input . It stands for the number of expressions to follow.
#Next T lines followed by expression
#Output format : For each expression print the value of expression

#3
#19 + 12 / 4 - ((4 - 7) * 3 / 1)
#1 + (2 - 3) * 4 + 5 - 6 * 8 - (18 * 12 * 13) - (11 / (5 + 2 + 4))
#((2 + 4) / 3 - 2 + 1)

#Output:
#31
#-2855
#1

def eval(expr):
    expr = expr.replace(' ', '')
    print(expr)
    n = []
    op = []
    vn = [str(c) for c in range(10)]
    vop = ['+', '-', '*', '/']        
    i=0
    while i < len(expr):
        
        print(str(n) + "---" + str(op))
          
        t = []
        while i<len(expr) and expr[i] in vn:
            t.append(expr[i])
            i = i + 1
        if len(t) > 0:
            n.append(int("".join(t)))
            if len(n) >= 2:
                if op[-1] == '*':
                    b = n.pop()
                    a = n.pop()
                    op.pop()   
                    n.append(a*b)
                elif op[-1] == '/':
                    b = n.pop()
                    a = n.pop()
                    op.pop()
                    n.append(int(a/b))   
        elif i<len(expr) and  expr[i] in vop:
            op.append(expr[i])
            i = i+1
        elif i<len(expr) and expr[i] == '(':
            s = ['(']
            p = ['(']
            i = i + 1
            while i<len(expr) and len(p)>0:
                if expr[i] in vop or expr[i] in vn:
                    s.append(expr[i])
                elif expr[i]=='(':
                    s.append('(')
                    p.append('(')
                elif expr[i]==')':
                    s.append(')')
                    p.pop()
                i=i+1    
            s = s[1:len(s)-1]
            r = eval("".join(s))
            n.append(r)
        else:
            i = i + 1    
    n.reverse()
    op.reverse() 
    print(str(n) + " - " + str(op))
    while len(n) >= 2:
        b = n.pop()
        a = n.pop()
        p = op.pop()
        if  p == '+':
            n.append(a+b)
        elif p == '-':
            n.append(a-b)
        elif p=='/':
            n.append(int(a/b))
        else:
            n.append(a*b)                       
    return n[0]



if __name__ == "__main__":
    tests = [("1+2",3), ("19+12/4-((4-7)*3/ 1)",31), 
             ("1 + (2 - 3) * 4 + 5 - 6 * 8 - (18 * 12 * 13) - (11 / (5 + 2 + 4)",-2855), ("((2 + 4) / 3 - 2 + 1)",1)] 
    for expr, expect_result in tests:
        result = eval(expr) 
        if result == expect_result:
            print("Test OK " + expr)
        else:
            print("Test NOK " + expr + " Expected " + str(expect_result) + " Got " + str(result))


