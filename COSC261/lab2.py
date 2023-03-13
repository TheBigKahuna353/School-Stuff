

def all_subsets(s):
    """Return a list of all subsets of the set s."""
    if len(s) == 0:
        return [set()]
    else:
        x = s.pop()
        subsets = all_subsets(s)
        return subsets + [subset | {x} for subset in subsets]

    

print(sorted(map(sorted, all_subsets({0, 1, 2}))))
print(sorted(map(sorted, all_subsets({'a', 'b'}))))
print({1} in all_subsets({0, 1, 2}))