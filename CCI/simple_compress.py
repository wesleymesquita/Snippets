def compress(s):
    cs = []
    i = 0
    while i < len(s):
        curr = s[i]
        c = 1
        while i+1 < len(s) and s[i+1]==curr:
            c = c+1
            i = i+1
        cs.append(curr)
        cs.append(str(c))
        i = i+1
    cs = "".join(cs)
    if len(cs) >= len(s):
        return s
    return cs


def test(test_data):
    for test in test_data:
        res = compress(test[0])
        if res == test[1]:
            print("Sucess ", test)
        else:
            print("Failure ", test, " got ", res)

if __name__ == '__main__':
    test([('aabcccccaaa', 'a2b1c5a3'), ('aa', 'aa'), ('abc', 'abc'), ('aaaaaa', 'a6')])
        
            
