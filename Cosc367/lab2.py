from search import *
from math import sqrt
from heapq import heappop, heappush

class LocationGraph(Graph):
    def __init__(self, location, radius, starting_nodes, goal_nodes):
        self.location = location
        self.radius = radius
        self._starting_nodes = starting_nodes
        self.goal_nodes = goal_nodes
    
    def starting_nodes(self):
        return self._starting_nodes
    
    def is_goal(self, node):
        return node in self.goal_nodes
    
    def outgoing_arcs(self, tail):
        for head in sorted(self.location.keys()):
            if head == tail:
                continue
            dist = self.euclidean_distance(tail, head)
            if dist <= self.radius:
                yield Arc(tail=tail, head=head,action=f"{tail}->{head}", cost=dist)

    def euclidean_distance(self, loc1, loc2):
        return sqrt((self.location[loc1][0] - self.location[loc2][0])**2 + (self.location[loc1][1] - self.location[loc2][1])**2)



class LCFSFrontier(Frontier):
    def __init__(self):
        self.heap = []
        self.index = 0
    
    def add(self, path):
        path_cost = sum(arc.cost for arc in path)
        heappush(self.heap, (path_cost, self.index, path))
        self.index += 1
    
    def __next__(self):
        while self.heap:
            return heappop(self.heap)[2]
        raise StopIteration


