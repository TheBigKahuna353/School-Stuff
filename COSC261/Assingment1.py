from dis import dis
from re import X
from tkinter.messagebox import NO


def format_sequence(converters_info, source_format, destination_format):
    if source_format == destination_format:
        return [source_format]
    graph = convert_graph(converters_info)
    parents, distances = dijkstra(graph, source_format)
    if parents[destination_format] is None:
        return "No solution!"
    temp = [destination_format]
    cur = destination_format
    while cur != source_format:
        cur = parents[cur]
        temp.append(cur)
    temp.reverse()
    return temp



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
            if not in_tree[v] and distance[u] + weight < distance[v]:
                distance[v] = weight + distance[u]
                parent[v] = u
    return (parent, distance)

def get_next_person(people):
    return people.index(False)

def bubbles(info):
    graph = convert_graph(info)
    leng = len(graph)
    people = [False for _ in range(leng)]
    lis = []
    while not all(people):
        start = get_next_person(people)
        parents, distances = dijkstra(graph, start)
        temp = [start]
        people[start] = True
        # print(parents)
        for i in range(leng):
            if parents[i] is not None:
                temp.append(i)
                people[i] = True
        lis.append(temp)
    return lis

def build_order(deps):
    deps = convert_graph(deps)
    return top_sort(deps)


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


def which_segments(city):
    graph = convert_graph(city)
    parents, distances = dijkstra(graph, 0, True)
    temp = []
    for i, x in enumerate(parents):
        if x is not None:
            temp.append((min(x, i), max(x, i)))
    return temp

def min_capacity(city_map, depot_position):
    graph = convert_graph(city_map)
    parents, distances = dijkstra(graph, depot_position, True)
    print(parents, distances)
    dist = max([x for x in distances if x != float('inf')]) * 2 # return trip
    if dist == float('inf'):
        return 0
    batt_needed = dist*3/2
    x = 4/3*batt_needed
    return int(x)

city_map = """\
U 4 W
0 2 5
0 3 2
3 2 2
"""

print(min_capacity(city_map, 0))
print(min_capacity(city_map, 1))
print(min_capacity(city_map, 2))
print(min_capacity(city_map, 3))
