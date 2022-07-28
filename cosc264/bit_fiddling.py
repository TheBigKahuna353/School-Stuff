def convert(x, base):
    if not isinstance(x, int):
        return -1
    if not isinstance(base, int):
        return -2
    if x < 0:
        return -3
    if base < 2:
        return -4
    lis = []
    while x > 0:
        lis.append(x % base)
        x = x // base
    lis.reverse()
    return lis

def hexstring(x):
    if not isinstance(x, int):
        return -1
    if x < 0:
        return -2
    lis = convert(x, 16)
    return "0x" + "".join(map(lambda x: hex(x)[2:], lis)).upper()

print(hexstring(1234))