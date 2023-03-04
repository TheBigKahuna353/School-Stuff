def all_strings(alpha, length):
    """returns a list containing all strings of the given length over the alphabet 
    alpha in no particular order. The alphabet alpha is a non-empty set of symbols, 
    each of which is a single-digit number or a single-character string, and length 
    is a non-negative integer."""

    if length == 0:
        return ['']
    else:
        return [str(x) + str(y) for x in alpha for y in all_strings(alpha, length - 1)]


print(sorted(all_strings({0, 1}, 3)))
print(sorted(all_strings({'a', 'b'}, 2)))


def DFA(alphabet):
    state = 0
    for symbol in alphabet:
        symbol = int(symbol)
        if state == 0:
            if symbol == 0:
                state = 1
            else:
                state = 3
        elif state == 1:
            if symbol == 0:
                state = 2
            else:
                state = 0
        elif state == 2:
            state = 2
        elif state == 3:
            if symbol == 0:
                state = 0
            else:
                state = 2
    return state == 0

total = 0
for i in range(4):
    for string in all_strings({1, 2, 3, 4, 5, 6, 7, 8}, i):
        total += 1
        print(string)
print(total)