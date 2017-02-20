def URLify(st):
    s = [c for c in st]
    nspaces = 0
    k = len(s)-1
    while s[k] == ' ':
        k = k -1
    j = k
    while j >=0:
        if s[j] == ' ':
            nspaces = nspaces + 1
        j = j-1
    j = k 
    while j >= 0:
        if s[j] != ' ':
            s[j+nspaces*2] = s[j]
            j = j-1
        else:
            s[j+nspaces*2] = '0'
            s[j+nspaces*2-1] = '2'
            s[j+nspaces*2-2] = '%'
            j = j-1
            nspaces = nspaces -1
    return "".join(s)

def test(test_data):
    for test in test_data:
        result = URLify(test[0])
        if result != test[1]:
            print("Error : failed on", test, "got ", result)
        else:
            print("Success for ", test, "got ", result)

if __name__ == "__main__":
    test_data  = [ ('Mr John Smith    ','Mr%20John%20Smith'), ('A B C    ', 'A%20B%20C')]
    test(test_data)
        
    
