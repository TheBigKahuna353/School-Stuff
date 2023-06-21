stack = []
vars = [None] * 10

def push(val):
    stack.append(val)

def pop():
    return stack.pop()

def add():
    val1 = pop()
    val2 = pop()
    push(val1 + val2)

def sub():
    val1 = pop()
    val2 = pop()
    push(val1 - val2)

def mul():
    val1 = pop()
    val2 = pop()
    push(val1 * val2)

def div():
    val1 = pop()
    val2 = pop()
    push(val1 / val2)

def store(var):
    val = pop()
    vars[var] = val

def load(var):
    push(vars[var])



i = 63
count = 0
while i > 1:
    i //= 2
    count += 1
print(count)