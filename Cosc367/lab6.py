import itertools
from csp import CSP, satisfies

def generate_and_test(obj):
    """Write a function generate_and_test that takes a CSP object 
    and returns an iterable (e.g. list, tuple, set, generator, ...) 
    of solutions. A solution is a complete assignment that satisfies 
    all the constraints."""
    names, domains = zip(*obj.var_domains.items())
    for values in itertools.product(*domains):
        assignment = {x:v for x, v in zip(names, values)}
        if all(satisfies(assignment, c) for c in obj.constraints):
            yield assignment



crossword_puzzle = CSP(
    var_domains={
        # read across:
        'across1': set("ant big bus car has".split()),
        'across3': set("book buys hold lane year".split()),
        'across4': set("ant big bus car has".split()),
        # read down:
        'down1': set("book buys hold lane year".split()),
        'down2': set("ginger search symbol syntax".split()),
        },
    constraints={
        lambda across1, down1: across1[0] == down1[0],
        lambda down1, across3: down1[2] == across3[0],
        lambda across1, down2: across1[2] == down2[0],
        lambda down2, across3: down2[2] == across3[2],
        lambda down2, across4: down2[4] == across4[0],
        })


solution = next(iter(generate_and_test(crossword_puzzle)))

# printing the puzzle similar to the way it actually  looks 
pretty_puzzle = ["".join(line) for line in itertools.zip_longest(
    solution['down1'], "", solution['down2'], fillvalue=" ")]
pretty_puzzle[0:5:2] = solution['across1'], solution['across3'], "  " + solution['across4']
print("\n".join(pretty_puzzle))

print(sorted(crossword_puzzle.var_domains['across1']))