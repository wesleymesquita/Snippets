#https://www.careercup.com/question?id=5752417288192000
# Goldman Sachs Interview Question for Associates

#    goldman-sachs-interview-questions

#    Algorithm to minimize number of trassaction.
#    Eg:
#    A->B = Rs. 5
#    B->C = Rs. 8
#    C->D = Rs. 9
#    A->D = Rs. 10
#    D->B = Rs. 11
#    C->A = Rs. 12

#    Minimize transactions

def min_transact(transacts):
    bal = {}
    for t in transacts:
        if t[0] not in bal:
            bal[t[0]] = -1*t[2]
        else:
            bal[t[0]] = bal[t[0]] - t[2]
        if t[1] not in bal:
            bal[t[1]] = t[2]
        else:
            bal[t[1]] = bal[t[1]] + t[2]
    obal = []
    for k in bal:
        obal.append([bal[k],k])
    obal = sorted(obal,key=lambda t:t[0])
    balanced = False
    i = 0
    j = len(obal)-1
    t = []
    print(obal)
    while not balanced:
        if obal[i][0]==0 and obal[j][0]==0:               
            return 0
        elif abs(obal[i][0]) == obal[j][0]:
            obal[i][0] = 0 
            obal[j][0] = 0
            t.append((obal[i][1], obal[j][1]))
            j = j-1
            i = i+1
        elif  abs(obal[i][0]) > obal[j][0]:
            obal[i][0] = obal[i][0] + obal[j][0]
            obal[j][0] = 0
            t.append((obal[i][1],obal[j][1]))
            j = j-1 
        else:
            obal[i][0] = 0
            obal[j][0] = obal[j][0]-abs(obal[i][0])
            i = i+1
            t.append((obal[i][1], obal[j][1]))
        if i == j:
            balanced=True
 
    return len(t)

if __name__ == "__main__":
    tests = [([('A','B',5), ('B','C',8), ('C','D',9), ('A','D',10), ('D','B',11), ('C','A',12)],3), ([('A','B',5),('B','C',5),('C','A',5)],0) ]
    for test, exp_result in tests:
        result = min_transact(test)
        if result == exp_result:
            print("OK Test \n\t" + str(test) + "\n")
        else:
            print("Error in Test: \n\t" + str(test) + "\n\t Expected " + str(exp_result) + " but GOT " + str(result) + "\n")  
    

