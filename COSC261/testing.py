def adjacency_list(text: str):
    lines = text.splitlines()
    leng = int(lines[0].split(" ")[1])
    weighted = "W" in lines[0]
    directed = "D" in lines[0]
    lis = [[] for _ in range(leng)]
    for line in lines[1:]:
        fields = line.split(" ")
        start = int(fields[0])
        stop = int(fields[1])
        weight = int(fields[2]) if weighted else None
        lis[start].append((stop, weight))
        if not directed:
            lis[stop].append((start, weight))
    return lis

def distance_matrix(adj):
    size = len(adj)
    matrix = [[float('inf') if x != y else 0 for x in range(size)] for y in range(size)]
    for i, x in enumerate(adj):
        for j, weight in x:
            matrix[i][j] = weight
    return matrix

def floyd(distance):
    matrix = distance
    size = len(matrix)
    dist = [[float('inf') if x != y else 0 for x in range(size)] for y in range(size)]
    for x in range(size):
        for y in range(size):
            if matrix[x][y] != float('inf'):
                dist[x][y] = matrix[x][y]
    for k in range(size):
        for i in range(size):
            for j in range(size):
                if dist[i][j] > dist[i][k] + dist[k][j]:
                    dist[i][j] = dist[i][k] + dist[k][j]
    return dist

def permutations(s):
    solutions = []
    dfs_backtrack((), s, solutions)
    return solutions


import copy
import enum
from tkinter.tix import Tree
from turtle import pos, position

def latin_squares(square):
    """Given a square (matrix) computes and returns Latin squares
    that can be obtained by replacing Nones with digits."""
    solutions = []
    dfs_backtrack(square, solutions)
    return solutions


def dfs_backtrack(candidate, output_data):
    # print(candidate)
    if should_prune(candidate):
        return
    if is_solution(candidate):
        add_to_output(candidate, output_data)
    else:
        for child_candidate in children(candidate):
            dfs_backtrack(child_candidate, output_data)

    
def add_to_output(candidate, output_data):
    output_data.append(copy.deepcopy(candidate))


def square_from_str(square_str):
    """Takes a string representation of a square and returns a matrix                                                                                                              
    (list of lists) representation where blanks are replaced with None."""
    return [[None if c == '-' else int(c) for c in line.strip()] for
            line in square_str.splitlines()]


def square_to_str(square):
    """Returns the string representation of the given square matrix."""
    return '\n'.join(''.join(str(c) for c in row) for row in square)

def is_solution(candidate):
    """Returns True if the candidate is a complete solution"""
    
    # Complete the code
    # test rows
    for row in candidate:
        test_row = [False for _ in range(len(row))]
        for x in row:
            if x is None:
                return False
    return True


def children(candidate):
    """Returns a collestion of candidates that are the children of the given
    candidate."""
    temp = []
    # Complete the code
    for x in range(len(candidate)):
        for y in range(len(candidate)):
            if candidate[x][y] is None:
                for z in range(len(candidate)):
                    child = copy.deepcopy(candidate)
                    child[x][y] = z
                    temp.append(child)
    return temp

    
def should_prune(candiate):
    """Returns True if the tree should be pruned at this point."""
    
    # Complete the code
    for x in range(len(candiate)):
        rows = []
        cols = []
        for y in range(len(candiate)):
            if candiate[x][y] is not None:
                if candiate[x][y] not in rows:
                    rows.append(candiate[x][y])
                else:
                    return True
            if candiate[y][x] is not None:
                if candiate[y][x] not in cols and candiate[y][x] is not None:
                    cols.append(candiate[y][x])
                else:
                    return True
    return False



# square = [
#     [0,    1],
#     [None, 0],
# ]


# solutions = latin_squares(square)
# print("Number of solutions:", len(solutions))
# for solution in solutions:
#     print(square_to_str(solution))


# square_str = """\
# 0123
# -0--  
# --0- 
# ----    
# """

# square = square_from_str(square_str)
# for solution in sorted(latin_squares(square)):
#     print(square_to_str(solution), end="\n\n")


#---------------------------------------------------------------------

def count_sort(seq, key):
    k = key_positions(seq, key)
    return sorted_array(seq, key, k)

def key_positions(seq, key):
    k = max(map(key, seq))+1
    c = [0] * k
    for a in seq:
        c[key(a)] += 1
    sum = 0
    for i in range(k):
        c[i], sum = sum, sum + c[i]
    return c

def sorted_array(seq, key, positions):
    out = [0] * len(seq)
    for a in seq:
        out[positions[key(a)]] = a
        positions[key(a)] += 1
    return out

def radix_sort(numbers, d):
    temp = numbers[:]
    for i in range(d):
        temp = count_sort(temp, lambda x: x // 10**i % 10)
        # print(temp)
    return temp
    
# print(radix_sort([329, 457, 657, 839, 436, 720, 355], 3))
