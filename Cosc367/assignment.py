from search import *
from math import sqrt, inf
from heapq import heappop, heappush

class RoutingGraph(Graph):

    directions = [('N', (-1, 0)), ('E', (0, 1)), ('S', (1, 0)), ('W', (0, -1))]

    def __init__(self, map_str):
        self.map_str = map_str.strip().split('\n')
        self.starting_nodes_list = []
        self.goal_nodes = []
        self.fuel_stations = []
        self.portals = []
        for x in range(len(self.map_str)):
            for y in range(len(self.map_str[x])):
                if self.map_str[x][y] == 'S':
                    self.starting_nodes_list.append((x, y, inf))
                if self.map_str[x][y].isdigit():
                    self.starting_nodes_list.append((x, y, int(self.map_str[x][y])))
                if self.map_str[x][y] == 'G':
                    self.goal_nodes.append((x, y))
                if self.map_str[x][y] == 'F':
                    self.fuel_stations.append((x, y))
                if self.map_str[x][y] == 'P':
                    self.portals.append((x, y))
                

    def is_goal(self, node):
        node = (node[0], node[1])
        return node in self.goal_nodes
    
    def starting_nodes(self):
        return self.starting_nodes_list
    
    def in_map(self, row, col):
        return  0 <= row < len(self.map_str) and 0 <= col < len(self.map_str[row])

    def outgoing_arcs(self, tail):
        cur_row, cur_col, cur_fuel = tail
        for action, (drow, dcol) in self.directions:
            row = cur_row + drow
            col = cur_col + dcol
            fuel = cur_fuel - 1
            if fuel < 0:
                continue
            if self.in_map(row, col):
                if self.map_str[row][col] not in 'X-|+':
                    yield Arc(tail, (row, col, fuel), action, 5)
        if (cur_row, cur_col) in self.fuel_stations and cur_fuel < 9:
            yield Arc(tail, (cur_row, cur_col, 9), 'Fuel up', 15)
        if (cur_row, cur_col) in self.portals:
            for portal in self.portals:
                if portal != (cur_row, cur_col):
                    row, col = portal
                    yield Arc(tail, (row, col, cur_fuel), f'Teleport to ({row}, {col})', 10)

    def estimated_cost_to_goal(self, node):
        return min([(abs(node[0] - goal[0]) + abs(node[1] - goal[1]))*5 for goal in self.goal_nodes])

class AStarFrontier(Frontier):

    def __init__(self, graph) -> None:
        self.container = []
        self.visited = set()
        self.graph = graph
        self.index = 0
    
    def add(self, path):
        path_cost = sum(arc.cost for arc in path)
        heappush(self.container, (path_cost + self.graph.estimated_cost_to_goal(path[-1].head), self.index, path))
        self.index += 1
    
    def __next__(self):
        while self.container:
            path_cost, _, path = heappop(self.container)
            if path[-1].head not in self.visited:
                self.visited.add(path[-1].head)
                return path
        raise StopIteration


def print_map(graph : RoutingGraph, frontier : AStarFrontier, solution):
    map_str = graph.map_str

    for node in frontier.visited:
        row, col, _ = node
        if map_str[row][col] in 'SG': continue
        map_str[row] = map_str[row][:col] + '.' + map_str[row][col+1:]
    
    if solution == None:
        print('\n'.join(map_str))
        return
    for arc in solution:
        if arc.tail == None:
            continue
        row, col, _ = arc.tail
        if map_str[row][col] in 'SG': continue
        map_str[row] = map_str[row][:col] + '*' + map_str[row][col+1:]
    
    print('\n'.join(map_str))


map_str = """\
+----------------+
|                |
|                |
|                |
|                |
|                |
|                |
|        S       |
|                |
|                |
|     G          |
|                |
|                |
|                |
+----------------+
"""

map_graph = RoutingGraph(map_str)
frontier = AStarFrontier(map_graph)
solution = next(generic_search(map_graph, frontier), None)
print_map(map_graph, frontier, solution)

map_str = """\
+-------+
|     XG|
|X XXX  |
|  S    |
+-------+
"""
map_graph = RoutingGraph(map_str)
frontier = AStarFrontier(map_graph)
solution = next(generic_search(map_graph, frontier), None)
print_map(map_graph, frontier, solution)

map_str = """\
+------------+
|         X  |
| S       X G|
|         X  |
|         X  |
|         X  |
+------------+
"""

map_graph = RoutingGraph(map_str)
frontier = AStarFrontier(map_graph)
solution = next(generic_search(map_graph, frontier), None)
print_map(map_graph, frontier, solution)

map_str = """\
+-------------+
|         G   |
| S           |
|         S   |
+-------------+
"""

map_graph = RoutingGraph(map_str)
frontier = AStarFrontier(map_graph)
solution = next(generic_search(map_graph, frontier), None)
print_map(map_graph, frontier, solution)

map_str = """\
+---------+
|         |
|    G    |
|         |
+---------+
"""

map_graph = RoutingGraph(map_str)
frontier = AStarFrontier(map_graph)
solution = next(generic_search(map_graph, frontier), None)
print_map(map_graph, frontier, solution)