#https://www.hackerrank.com/challenges/dynamic-array
class DArray:
    def __init__(self, N):
        self.N = N
        self.arr = []        
        i = 0
        while i < N:
            self.arr.append([])
            i = i +1
        self.lastAns = 0
    def exec_cmd1(self,x,y):
        idx = (x^self.lastAns)%self.N
        self.arr[idx].append(y)                
    def exec_cmd2(self,x,y):
        idx = (x^self.lastAns)%self.N
        self.lastAns = self.arr[idx][y%len(self.arr[idx])]
        print(self.lastAns)        
    def execute_cmd(self,cmd,x, y):
        if cmd == 1:
            self.exec_cmd1(x,y)
        elif cmd==2:
            self.exec_cmd2(x,y)
    
if __name__ == '__main__':
    N,Q = input().split()
    N,Q = [int(N), int(Q)]
    darr = DArray(N) 
    i=0
    while i<Q:
        cmd = input().split()
        c,x,y = [int(e) for e in cmd]
        darr.execute_cmd(c,x,y)
        i = i+1
