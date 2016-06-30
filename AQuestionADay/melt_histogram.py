#
# Goldman-sachs-interview-questions
# Visit : https://www.careercup.com/question?id=5650516169195520 
#Given a histogram chart with values say {5,4,3,6,0,1}. Get the total count required to completely melt the histogram. A column with value 5 has 5 blocks in it. Any block which has air on any of its side gets melted.

#Sample 1

#{5,4,3,6,0,1} - > {0,3,2,0,0,0}->{0,0,0,0,0,0} => count=2

#Sample 2

#{0,1,1,1,1,0} - > {0,0,0,0,0,0} => count=1

def melt_hist(hist):
    if len(hist) == 1 or len(hist) == 2:
        return 1;
    is_melt = False
    count = 0
    while not is_melt:
        h = hist[:]
        h[0]=0    
        for i in range(1,len(hist)-1):
            k = min(min(hist[i-1], hist[i]), hist[i+1])
            if k>0 and k == hist[i]:
                k=k-1
            h[i]=k     
        h[len(h)-1] = 0
        hist = h[:]         
        count = count + 1
        if len([c for c in hist if c != 0])==0:
            is_melt=True
    return count 
        

    return 0     

if __name__ == "__main__":
    tests = [ ([5,4,3,6,0,1],2),
              ([0,1,1,1,0],1),
              ([2,2,2,2],2) 
        ]
    for test, result  in tests:
        if melt_hist(test) != result:
            print("Error in " + str(test))
        else:
            print("OK for " + str(test))  
