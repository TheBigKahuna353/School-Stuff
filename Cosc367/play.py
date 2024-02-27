# Strings used in this problem:

states = {
    "Odd": 0,
    "Even": 1,
    "no one": 2,
    0: "Odd",
    1: "Even",
    2: "no one"
}

def valid_spots(arr, player):
    for i in range(player, len(arr)-1, 2):
        if arr[i] is None:
            yield i

def get_lowest_number(arr, player):
    numbers = [2*i+player for i in range(len(arr)-1)]
    for i in range(player, len(arr)-1):
        if arr[i] is not None:
            numbers.remove(arr[i])
    return numbers[0]

def valid(arr, player):
    cur = -1
    for i in range(player, len(arr)-1):
        if arr[i] is not None:
            if arr[i] < cur:
                return False
            cur = arr[i]
    return True

def get_other_player(player):
    states[(player + 1) % 2]

def play(array, next_to_play):
    player = states[next_to_play]
    for 


print(play([None, None], 'Even'))