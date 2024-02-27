

def n_queens_neighbours(state):
    neighbours = []
    for i in range(len(state)-1):
        for j in range(i+1, len(state)):
            neighbour = list(state)
            neighbour[i], neighbour[j] = neighbour[j], neighbour[i]
            neighbours.append(tuple(neighbour))

            
    return sorted(neighbours)


def n_queens_cost(state):
    cost = 0
    for i in range(len(state)-1):
        for j in range(i+1, len(state)):
            if abs(state[i] - state[j]) == abs(i - j):
                cost += 1
    return cost


def greedy_descent(initial_state, neighbours, cost):
    state = initial_state
    states = [initial_state]
    while True:
        neighbour_list = neighbours(state)
        if len(neighbour_list) == 0:
            return states
        best_neighbour = min(neighbour_list, key=cost)
        if cost(best_neighbour) >= cost(state):
            return states
        state = best_neighbour
        states.append(state)
    
import random
N = 8
random.seed(0)

def random_state():
    return tuple(random.sample(range(1,N+1), N))   

def greedy_descent_with_random_restart(random_state, neighbours, cost):
    """When the search reaches a local minimum that is not global, the procedure must print RESTART and restart the search by calling random_state."""
    state = random_state()
    while cost(state) > 0:
        states = greedy_descent(state, neighbours, cost)
        for s in states:
            print(s)
        state = states[-1]
        if cost(state) == 0:
            return 
        print("RESTART")
        state = random_state()
    print(state)


def roulette_wheel_select(population, fitness, r):
    """The function returns an individual from the population with probability proportional to its fitness."""
    total_fitness = sum(fitness(individual) for individual in population)
    num = total_fitness * r
    for individual in population:
        num -= fitness(individual)
        if num <= 0:
            return individual
        