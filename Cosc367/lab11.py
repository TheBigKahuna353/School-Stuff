"""
Game Trees
"""

def max_value(tree):
    if isinstance(tree, int):
        return tree
    else:
        return max(list(map(min_value, tree)))

def min_value(tree):
    if isinstance(tree, int):
        return tree
    else:
        return min(list(map(max_value, tree)))


def max_action_value(tree):
    if isinstance(tree, int):
        return None, tree
    action, util = max(enumerate(tree), key=lambda x: min_value(x[1]))
    return action, min_value(util)

def min_action_value(tree):
    if isinstance(tree, int):
        return None, tree
    action, util = min(enumerate(tree), key=lambda x: max_value(x[1]))
    return action, max_value(util)

