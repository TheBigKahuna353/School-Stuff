

def interpretations(atoms):
    """
    :param atoms: a set of atoms
    :return: a list of all possible interpretations of these atoms
    """

    atoms = sorted(atoms)

    interpretation = [{atom:False for atom in atoms} for i in range(2**len(atoms))]
    
    for i in range(2**len(atoms)):
        for j in range(len(atoms)):
            if i & (1 << j):
                interpretation[i][atoms[len(atoms) - j - 1]] = True

    return interpretation



def get_atoms(formula):
    """Takes a formula in the form of a lambda expression and returns a set of
    atoms used in the formula. The atoms are parameter names represented as
    strings.
    """
    
    return {atom for atom in formula.__code__.co_varnames}
    
def value(formula, interpretation):
    """Takes a formula in the form of a lambda expression and an interpretation
    in the form of a dictionary, and evaluates the formula with the given
    interpretation and returns the result. The interpretation may contain
    more atoms than needed for the single formula.
    """
    arguments = {atom: interpretation[atom] for atom in get_atoms(formula)}
    return formula(**arguments)

def models(knowledge_base):
    """
    :param knowledge_base: a knowledge base, a set of lambda expressions
    :return: a list of all possible models of this knowledge base
    """

    atoms = set()
    for formula in knowledge_base:
        atoms = atoms.union(get_atoms(formula))
    

    models = []
    for interpretation in interpretations(atoms):
        if all(value(formula, interpretation) for formula in knowledge_base):
            models.append(interpretation)
    
    return models
   

   
knowledge_base = {
    lambda a, b: a and not b,
    lambda c: c
}

print(models(knowledge_base))

knowledge_base = {
    lambda a, b: a and not b,
    lambda c, d: c or d
}

for interpretation in models(knowledge_base):
    print(interpretation)