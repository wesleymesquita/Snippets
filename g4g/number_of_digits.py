#http://www.practice.geeksforgeeks.org/problem-page.php?pid=1392
#Number of digits
#code
fib = [0,1,1]
for i in range(3,1000):
    fib.append(fib[-2] + fib[-1])
T = int(raw_input())
for t in range(0, T):
    nfib = int(raw_input())
    print len(str(fib[nfib]))