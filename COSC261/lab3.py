

def epsilon_closure(state, nfa):
    """returns a set of all the states in the epsilon closure of the given state of the given nfa with epsilon transitions."""
    open = [state]
    closed = []
    closures = {state}
    while open:
        s = open.pop()
        if s not in closed:
            closed.append(s)
            if "_" in nfa[s]:
                open.extend(nfa[s]["_"])
                closures.update(nfa[s]["_"])
    return closures


# The NFA pictured above
nfa = {0: {"_": {1}, "a": {1, 2}, "b": {2}},
       1: {"_": {2}, "a": {1}, "b": {0}},
       2: {"a": {1}, "b": {2}}
      }
for i in range(3):
    print(f"Epsilon closure for q{i}: {sorted(epsilon_closure(i, nfa))}")


# These epsilon transitions form a loop - be sure to keep track of where you've been!
loopy_nfa = {
       0: {"_": {1}, "a": {1}, "b": {2}},
       1: {"_": {2}, "a": {1}, "b": {0}},
       2: {"_": {0}, "a": {1}, "b": {2}}
      }
for i in range(3):
    print(f"Epsilon closure for q{i}: {sorted(epsilon_closure(i, loopy_nfa))}")