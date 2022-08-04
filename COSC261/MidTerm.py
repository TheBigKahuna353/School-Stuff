

from tkinter import N


def dfs_backtrack(candidate, output_data):
    # print(candidate)
    if should_prune(candidate):
        return
    if is_solution(candidate):
        add_to_output(candidate, output_data)
    else:
        for child_candidate in children(candidate):
            dfs_backtrack(child_candidate, output_data)

def should_prune(canditate):
    return False

def is_solution(canditate):
    pass

def add_to_output(candiadate, output):
    output.append(candiadate)

def children(candiate):
    pass

#-----------------------------------------------------------------------------

def convert_graph(text: str):
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


def next_vertex(in_tree, distance):
    low_index = -1
    low_val = float('inf')
    for i in range(len(in_tree)):
        if in_tree[i]:
            continue
        if distance[i] < low_val:
            low_val = distance[i]
            low_index = i
    return low_index  

def dijkstra(adj_list, start, weighted = False, ):
    n = len(adj_list)
    in_tree = [False for _ in range(n)]
    distance = [float('inf') for _ in range(n)]
    parent = [None for _ in range(n)]
    distance[start] = 0
    while not all(in_tree):
        u = next_vertex(in_tree, distance)
        if u == -1:
            break
        in_tree[u] = True
        for v, weight in adj_list[u]:
            weight = 1 if not weighted else weight
            if not in_tree[v] and weight < distance[v]:
                distance[v] = weight
                parent[v] = u
    return (parent, distance)

#-----------------------------------------------------------------------

def top_sort(adj):
    n = len(adj)
    found = [False for _ in range(n)]
    stack = []
    for i in range(n):
        if not found[i]:
            top_help(i, adj, found, stack)
    stack.reverse()
    return stack

def top_help(u, adj, found, stack):
    found[u] = True
    for i, _ in adj[u]:
        if not found[i]:
            top_help(i, adj, found, stack)
    stack.append(u)


#------------------------------------------------------------------------

def all_odds(numbers):
    if len(numbers) == 0:
        return True
    if numbers[-1] % 2 == 0:
        return False
    return all_odds(numbers[:-1])

def bts(adj, s):
    n = len(adj)
    state = ["u"] * n
    parent = [None] * n
    q = []
    state[s] = "d"
    q.append(s)
    return bts_loop(adj, q, state, parent)

def bts_loop(adj, q, state, parent):
    while len(q) != 0:
        u = q.pop(0)
        for v, weight in adj[u]:
            if state[v] == "u":
                state[v] = "d"
                parent[v] = u
                q.append(v)
        state[u] = "p"
    return parent


def reaching_vertices(adj_list, target):
    temp = [target]
    for i in range(len(adj_list)):
        if i == target:
            continue
        parents, distances = dijkstra(adj_list, i)
        if parents[target] is not None:
            temp.append(i)
    return temp


def min_energy(campus_map):
    graph = convert_graph(campus_map)
    parents, distance = dijkstra(graph, 0, True)
    return sum(distance)

campus_map = """\
U 3 W
0 1 1
2 1 2
2 0 4
"""

print(min_energy(campus_map))
