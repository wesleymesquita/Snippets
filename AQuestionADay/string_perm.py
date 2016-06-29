import os


def get_all_perms(s):
    all_perms = []
    gen_perms(s, [], all_perms)
    return all_perms

def gen_perms(s, l=[], all_perms=[]):
    """"Returns all  permutations of given string s"""    
    if len(s) == 1:
        l.append(s[0])
        all_perms.append((''.join(l)))
    else:
        for i in range(0, len(s)):
            nl = l[:]
            nl.append(s[i])
            sub = s[0:i] + s[i+1:len(s)]
            gen_perms(sub, nl, all_perms)
        
if __name__ == "__main__":
    if len(os.sys.argv) != 2:
        print("Usage: python3 string_perm.py SomeString")    
    else:
        perms = get_all_perms(os.sys.argv[1])
        print("Generated " + str(len(perms)) + " permutations")
        for perm in perms:
            print(perm, end='\t') 
        print("")
