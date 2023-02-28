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

def itinerary(adj_list, start, end):
    if start == end:
        return [(start, 0)]
    parent, distance = dijkstra(adj_list, start)
    if parent[end] is None:
        return []
    path = [end]
    time = []
    while end != start:
        time.append(distance[end])
        end = parent[end]
        path.append(end)
    path.reverse()
    time.reverse()
    path = [(x, sum(time[:i])) for i, x in enumerate(path)]
    return path


def dijkstra(adj_list, start):
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
            weight =  weight
            if not in_tree[v] and weight < distance[v]:
                distance[v] = weight
                parent[v] = u
    return (parent, distance)

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

def cost(a, b, na=None, nb=None):
    """ Cost of converting first na chars of a into first nb chars of b """
    if na is None:  # Top level call - both na and nb will be None
        na = len(a)
        nb = len(b)
    if na == 0 or nb == 0:
        # One string is empty - n insertions or deletions required
        return max(na, nb) 
    elif a[na - 1] == b[nb - 1]:  # Do last chars match?
        return cost(a, b, na - 1, nb - 1)  # Yes - this is the align/copy case
    else:  # Last chars don't match
        # Must delete last a, insert last b or replace last a with last b
        delete_cost = 1 + cost(a, b, na - 1, nb)
        insert_cost = 1 + cost(a, b, na, nb - 1)
        replace_cost = 1 + cost(a, b, na - 1, nb - 1)
        return min(delete_cost, insert_cost, replace_cost)


class Vec:
    """A simple vector in 2D. Can also be used as a position vector from
       origin to define points.
    """
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __repr__(self):
        """Return this point/vector as a string in the form "(x, y)" """
        return "({}, {})".format(self.x, self.y)

    def __add__(self, other):
        """Vector addition"""
        return Vec(self.x + other.x, self.y + other.y)

    def __sub__(self, other):
        """Vector subtraction"""
        return Vec(self.x - other.x, self.y - other.y)
    
    def __mul__(self, scale):
        """Multiplication by a scalar"""
        return Vec(self.x * scale, self.y * scale)

    def dot(self, other):
        """Dot product"""
        return self.x * other.x + self.y * other.y

    def lensq(self):
        """The square of the length"""
        return self.dot(self)


def is_ccw(a, b, c):
    """True iff triangle abc is counter-clockwise."""
    p = b - a
    q = c - a
    area = p.x * q.y - q.x * p.y
    # May want to throw an exception if area == 0
    return area > 0

def contains(poly1, poly2):
    min_x = min(poly1, key=lambda p: p.x).x
    max_x = max(poly1, key=lambda p: p.x).x
    min_y = min(poly1, key=lambda p: p.y).y
    max_y = max(poly1, key=lambda p: p.y).y
    for p in poly2:
        if p.x <= min_x or p.x >= max_x or p.y <= min_y or p.y >= max_y:
            return False
    return True

# poly1 = [Vec(0,0), Vec(20,0), Vec(20,20), Vec(0,20), Vec(0,0)]
# poly2 = [Vec(5,5), Vec(10,5), Vec(5,10), Vec(5,5)]
# print(contains(poly1, poly2))

# poly1 = [Vec(0,0), Vec(20,0), Vec(20,20), Vec(0,20), Vec(0,0)]
# poly2 = [Vec(5,5), Vec(10,5), Vec(5,10), Vec(5,5)]
# print(contains(poly2, poly1))

 	

# poly1 = [Vec(0,0), Vec(10,0), Vec(5,5), Vec(10,10), Vec(0, 10), Vec(0,0)]
# poly2 = [Vec(8,4), Vec(9,4), Vec(9,6), Vec(8,6), Vec(8,4)]
# print(contains(poly1, poly2))


def change(value, coinage):

    cache = {}
    def helper(value, coinage):
        """
        value: int
        coinage: list of tuples (int, int)
        """
        if value == 0:
            return []
        if sum(coinage) == 0:
            return []
        if value in cache:
            return cache[(value, coinage)]
        for coin, count in coinage:
            if count <= 0:
                continue
            if coin <= value:
                c2 = coinage.copy()
                c2[coin] -= 1
                way = helper(value - coin, c2)
                if way:
                    cache[value] = max([coin] + way, cache[value])
        return cache[value]
        
    coinage = {coin:ammount for (coin, ammount) in coinage}
    best = helper(value, coinage)
    return best
    

print(change(32, [(1, 9), (10, 5), (25, 3)]))