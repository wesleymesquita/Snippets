def sum_inc(s):
    numbers = s.split(sep='+')
    numbers = [int(n) for n in numbers]
    numbers = sorted(numbers)
    first = True
    res = ''
    for n in numbers:
        
        if first:
            first = False
        else:
            res = res + '+'
        res = res + str(n)
        
    return res    

if __name__ == '__main__':
    s = input()
    print(sum_inc(s))
