def generate_perm(st):
    perm(st, "")

def perm(rem, prefix):
    if len(rem) == 0:
        print(prefix)
    else:
        i=0
        while i<len(rem):
            r = rem[0:i] + rem[i+1:]
            perm(r, prefix + rem[i])
            i = i+1

def test(st):
    generate_perm(st)


if __name__ == "__main__":
    test('ABCD')
