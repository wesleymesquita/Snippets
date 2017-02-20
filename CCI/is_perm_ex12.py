def is_perm(sa, sb):
    return sorted(sa) == sorted(sb)

if __name__ == "__main__":
    print(is_perm('ASDF', 'FDSA'))
    print(is_perm('ASD', 'ASDFG'))
    print(is_perm('A', 'A'))
    print(is_perm('', ''))

            

