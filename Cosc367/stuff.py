

def interpretations(atoms):
    atoms = sorted(atoms)
    first = [{atoms[0]: False}, {atoms[0]: True}]
    if len(atoms) == 1:
        return first
    rest = interpretations(atoms[1:])
    lis = []
    for i in first:
        for j in rest:
            lis.append({**i, **j})
    return lis
    
atoms = {'q', 'p', 'r'}
for i in interpretations(atoms):
    print(i)