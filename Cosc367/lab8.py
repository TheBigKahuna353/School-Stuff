def joint_prob(network, assignment):
    
    # If you wish you can use the following template
    
    p = 1 # p will eventually hold the value we are interested in
    for var in network:
        # Extract the probability of var=true from the network
        # by finding the right assignment for Parents and getting the
        # corresponding CPT. 
        
        # Update p by multiplying it by probablity var=true or var=false
        # depending on how var appears in the given assignment.
        cpt = network[var]['CPT']
        parents = network[var]['Parents']
        if len(parents) == 0:
            p *= cpt[()] if assignment[var] else 1 - cpt[()]
        else:
            parent_values = tuple(assignment[parent] for parent in parents)
            p *= cpt[parent_values] if assignment[var] else 1 - cpt[parent_values]
    return p


def normalize(Q):
    alpha = 1 / sum(Q.values())
    for key in Q:
        Q[key] *= alpha
    return Q

def enumerate_all(network, assignment):
    if len(assignment) == len(network):
        print(assignment)
        return joint_prob(network, assignment)
    var = next(var for var in network if var not in assignment) # select a variable not in assignment
    return sum(enumerate_all(network, {**assignment, var: val}) # extend assignment by setting var=True/False and sum
               for val in [True, False])

def query(network, query_var, evidence):
    # When the argument evidence is an empty dictionary we are (semantically)
    #  asking for the prior probability of query_var. The algorithm, however, 
    # remains the same.
    Q = {}
    for val in [True, False]:
        Q[val] = enumerate_all(network, {**evidence, query_var: val})
    return normalize(Q)


network = {
    'A': {
        'Parents': [],
        'CPT': {
            (): 0.2
            }},
}

answer = query(network, 'A', {})
print("P(A=true) = {:.5f}".format(answer[True]))
print("P(A=false) = {:.5f}".format(answer[False]))

network = {
    'A': {
        'Parents': [],
        'CPT': {
            (): 0.1
            }},
            
    'B': {
        'Parents': ['A'],
        'CPT': {
            (True,): 0.8,
            (False,): 0.7,
            }},
    }
 
answer = query(network, 'B', {'A': False})
print("P(B=true|A=false) = {:.5f}".format(answer[True]))
print("P(B=false|A=false) = {:.5f}".format(answer[False]))

network = {
    'A': {
        'Parents': [],
        'CPT': {
            (): 0.1
            }},
            
    'B': {
        'Parents': ['A'],
        'CPT': {
            (True,): 0.8,
            (False,): 0.7,
            }},
    }
 
answer = query(network, 'B', {})
print("P(B=true) = {:.5f}".format(answer[True]))
print("P(B=false) = {:.5f}".format(answer[False]))