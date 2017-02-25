#http://codeforces.com/problemset/problem/131/A
def fix_case(s):
    if len(s) == 0:
        return s
    elif len(s) == 1:
        if s.islower():
            return s.upper()
        return s.lower()
    else:
        convert = True
        i = 1
        while i < len(s):
            if s[i].islower():
                convert = False
                break
            i = i + 1
        if convert:
            r = [c for c in s.lower()]         
            if s[0].islower():
                 r[0] = r[0].upper()
            return ''.join(r)
            
        return s
if __name__ == '__main__':
    s = input()
    print(fix_case(s))
