#https://www.hackerrank.com/contests/booking-passions-hacked-backend/challenges/good-memories/

class Node:
    def __init__(self, nid):
        self.nid = nid
        self.neighbors = {}
class Graph:
    def __init__(self):
        self.nodes = {}
    def get_node(self, nid):
        try:
            n = self.nodes[nid]
            return n
        except:
            return None
    def add_edge(self, uid, vid):
        u = self.get_node(uid)
        v = self.get_node(vid)
        if u == None:
            u = Node(uid)
            self.nodes[uid] = u
        if v == None:
            v = Node(vid)
            self.nodes[vid] = v
        self.nodes[uid].neighbors[vid] = v

def calc_incoming(G):
    inc = {}
    for n in G.nodes:
        inc[n] = 0
    for n in inc:
        for ne in G.nodes[n].neighbors:
            inc[ne] = inc[ne] + 1
    return inc

def topo_sort(G):
    inc = calc_incoming(G)
    q = [n for n in inc if inc[n] == 0]
    topo = []
    while len(q) > 0:
        curr_n = q.pop(0)
        for n in G.nodes[curr_n].neighbors:
            inc[n] = inc[n] - 1
            if inc[n] == 0:
                q.append(n)
        topo.append(curr_n) 
    if len(G.nodes) != len(topo):   
        print('ORDER VIOLATION') 
    else:
        print('ORDER EXISTS')

if __name__ == '__main__':
    X = int(input())
    for x in range(X):
        G = Graph()        
        N = int(input())        
        for n in range(N):
            hops = input().split(sep=',')
            for h in range(1,len(hops)):
                G.add_edge(hops[h-1], hops[h])
        topo_sort(G)                               
      

