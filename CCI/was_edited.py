def was_edited(a, b):
    la = len(a)
    lb = len(b)
    if abs(la-lb) > 1:
        return False
    if lb == la:
        i = 0
        c = 0
        while i < lb:
            if a[i] != b[i]:
                c = c + 1
            if c > 1:
                return False
            i = i + 1
    elif la > lb:
        i = 0
        while i < lb:
            if a[i] != b[i]:
                j = i + 1
                while i < lb:
                    if a[j] != b[i]:
                        print(j,i)
                        return False
                    i = i+1
                    j = j+1
            i = i + 1
    else:
        i = 0
        while i < la:
            if a[i] != b[i]:
                j = i + 1
                while i < la:
                    if a[i] != b[j]:
                        return False
                    i = i+1
                    j = j+1
            i = i+1
    return True

def test(test_data):
    for test in test_data:
        res = was_edited(test[0], test[1])
        if res != test[2]:
            print("Failed : ", test, " got ", res)
        else:
            print("Succes : ", test)


if __name__ == '__main__':
    test([('pale', 'ple', True), ('pales', 'pale', True), ('pale', 'bale',True), ('pale', 'bake', False)])
