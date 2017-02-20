def check_is_unique(st):
    if len(st) == 0:
        return False
    elif len(st) == 1:
        return True
    else:
        s = sorted(st)
        for i in range(0, len(s)-1):
            if s[i] == s[i+1]:
                return False

    return True

def test(st_arr, exp_res):
    is_unique  = [check_is_unique(st) for st in st_arr]
    if is_unique != exp_res:
        return False
    return True

if __name__ == "__main__":
    st_arr = ["ASDFG", "AASDFG", "", "A", "BAABABABA"]
    exp_res = [True, False, False, True, False]
    result = test(st_arr, exp_res)
    if result :
        print("Test went fine")
    else:
        print("Test failed:")
    


