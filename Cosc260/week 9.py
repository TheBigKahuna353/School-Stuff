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
        
def max_value(items, cap):
    
    cache = {}

    def best_item(n):
        if n == len(items):
            return 0
        if items[n] in cache:
            benefit = 1
        benefit = items[n].value / items[n].weight
        bene2, n2 = best_item(n+1)
        return n if benefit > bene2 else n2
