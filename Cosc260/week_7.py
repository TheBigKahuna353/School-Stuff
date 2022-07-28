import sys
sys.setrecursionlimit(2000)

class Item:
    """An item to (maybe) put in a knapsack. Weight must be an int."""
    def __init__(self, value, weight):
        self.value = value
        self.weight = weight

    def __repr__(self):
        """The representation of an item"""
        return f"Item({self.value}, {self.weight})"
        

def max_value(items: list, cap):
    cache = {}

    def helper(items:list, cap, i):
        if i < 0:
            return 0
        item = items[i]
        if cap - item.weight < 0:
            if (cap, i-1) in cache:
                return cache[(cap, i-1)]
            a = helper(items, cap, i-1)
            cache[(cap, i-1)] = a
            return a
        if (cap, i-1) in cache:
            a = cache[(cap, i-1)]
        else:
            a = helper(items, cap, i-1)
            cache[(cap, i-1)] = a
        if (cap - item.weight, i-1) in cache:
            b = cache[(cap, i-1)]
        else:
            b = helper(items, cap - item.weight, i-1)
            cache[(cap - item.weight, i-1)] = b
            b += item.value
        return max(a, b)
    
    a = helper(items, cap, len(items)-1)
    return a
    



 	

# A large problem (500 items)
import random
random.seed(12345)  # So everyone gets the same

items = [Item(random.randint(1, 100), random.randint(1, 100)) for i in range(500)]
print(max_value(items, 500))


 	

# The example from the lecture notes
items = [
    Item(45, 3),
    Item(45, 3),
    Item(80, 4),
    Item(80, 5),
    Item(100, 8)]

print(max_value(items, 10))

items = [Item(i, 10) for i in range(1, 11)]
items.extend([Item(1, 5), Item(1, 4)])

random.seed(12345)

for x in range(10):
    random.shuffle(items)
    print(max_value(items, 99))