


def is_valid_expression(object, function_symbols, leaf_symbols):
    if isinstance(object, str):
        return object in leaf_symbols
    elif isinstance(object, int):
        return True
    elif isinstance(object, tuple) or isinstance(object, list):
        if len(object) == 3:
            if object[0] in function_symbols:
                return is_valid_expression(object[1], function_symbols, leaf_symbols) and is_valid_expression(object[2], function_symbols, leaf_symbols)
            else:
                return False
        else:
            return False
    else:
        return False




def depth(expression):
    if isinstance(expression, str) or isinstance(expression, int):
        return 1
    elif isinstance(expression, tuple) or isinstance(expression, list):
        return 1 + max(depth(expression[1]), depth(expression[2]))
    else:
        return 0

def evaluate(expression, bindings):
    if isinstance(expression, str):
        return bindings[expression]
    elif isinstance(expression, int):
        return expression
    elif isinstance(expression, tuple) or isinstance(expression, list):
        return bindings[expression[0]](evaluate(expression[1], bindings), evaluate(expression[2], bindings))

import random

def random_expression(function_symbols, leaves, max_depth):
    max_depth = random.randint(0, max_depth)
    if max_depth <= 0:
        return random.choice(leaves)
    else:
        return [random.choice(function_symbols), random_expression(function_symbols, leaves, max_depth - 1), random_expression(function_symbols, leaves, max_depth - 1)]



def generate_rest(initial_sequence, expression, length):
    i = len(initial_sequence)
    x = initial_sequence[i-2]
    y = initial_sequence[i-1]
    seq = []
    while i < length + len(initial_sequence):
        seq.append(evaluate(expression, {'i': i, 'x': x, 'y': y, 
                                         '+': lambda x, y: x + y,
                                         '*': lambda x, y: x * y, 
                                         '-': lambda x, y: x - y, 
                                         '/': lambda x, y: x / y}))
        x = y
        y = seq[-1]
        i += 1
    return seq


def check_sequence(sequence, expression):
    i = 2
    while i < len(sequence):
        if sequence[i] != evaluate(expression, {'i': i, 'x': sequence[i-2], 'y': sequence[i-1], 
                                         '+': lambda x, y: x + y,
                                         '*': lambda x, y: x * y, 
                                         '-': lambda x, y: x - y, 
                                         '/': lambda x, y: x / y}):
            return False
        i += 1
    return True

def predict_rest(sequence):
    random.seed(0)
    function_symbols = ['+', '-', '*']
    leaves = ['i', 'x', 'y'] + list(range(-2, 3))
    max_depth = 3
    expression = random_expression(function_symbols, leaves, max_depth)
    while not check_sequence(sequence, expression):
        expression = random_expression(function_symbols, leaves, max_depth)
    return generate_rest(sequence, expression, 5)



sequence = [0, -1, 1, 0, 1, -1, 2, -1]
print(predict_rest(sequence))