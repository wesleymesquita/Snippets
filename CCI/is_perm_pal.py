def is_perm_pal(st):
    count_letters = {}
    for c in st:
        cl = c.lower() 
        if cl.isalpha():
            if cl not in count_letters:
                count_letters[cl] = 1
            else:
                count_letters[cl] = count_letters[cl]+1
    odds = 0
    for k in count_letters:
        if count_letters[k]%2 == 1:
            odds = odds+1
    if odds == 0 or odds == 1:
        return True
    return False

def test(test_data):
    for test in test_data:
        res = is_perm_pal(test[0])
        if res != test[1]:
            print("Failed on ", test, " got ", res)
        else:
            print("Success on ", test)

if __name__ == '__main__':
    test([('Tact Coa', True)])

