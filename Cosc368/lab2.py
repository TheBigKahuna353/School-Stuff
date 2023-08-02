from tkinter import *
from tkinter.ttk import * 
import random
import time

window = Tk()

board = 'qwertyuiopasdfghjklzxcvbnm'
board_size = [10, 9, 7]


frameBottom = Frame(window, borderwidth=1, relief="solid", padding=10)
frameBottom.pack(side=BOTTOM, padx=10, pady=10)

frameTop = Frame(window)
frameTop.pack(side=TOP, fill=X, padx=10, pady=10)

label = Label(frameTop)
label.pack(side=TOP)

current_block = 2
btns = []

start_time = time.time()

condition = 'Dynamic' # set to 'Dynamic' or 'Static'

def set_target_letters():
    letters = 'abcdefghijklmnopqrstuvwxyz'
    target_letters = ''.join(random.sample(letters, 6))
    return target_letters

target_letters = set_target_letters()
target = target_letters

def shuffle():
    global board
    board = ''.join(random.sample(board, len(board)))
    for i, btn in enumerate(btns):
        btn['text'] = board[i]
        btn['command'] = lambda letter=board[i]: click(letter)

def log_time(char, block, time):
    with open('log.txt', 'a') as f:
        f.write(f'Jordan {condition} {char} {block} {time}\n')

def update_label():
    global current_block
    global target

    if len(target) > 0:
        letter = random.choice(target)
        target = target.replace(letter, '')
        label['text'] = letter
    else:
        if current_block > 0:
            current_block -= 1
            target = target_letters
            update_label()
        else:
            label['text'] = 'Done!'
    

def button(parentFrame, letter):
    frame = Frame(parentFrame, height=64, width=64)
    frame.pack_propagate(0) # don't shrink
    btn = Button(frame, text=letter, command=lambda letter=letter: click(letter))
    btn.pack(fill=BOTH, expand=1)
    frame.pack(side=LEFT)
    btns.append(btn)

def click(letter):
    global start_time
    if letter == label['text']:
        time_taken = (time.time() - start_time) * 1000
        log_time(label['text'], current_block, time_taken)
        start_time = time.time()
        update_label()
        if condition == 'Dynamic':
            shuffle()

def get_index(x, y):
    if x == 0:
        return y
    elif x == 1:
        return board_size[0] + y
    else:
        return board_size[0] + board_size[1] + y

for row, length in enumerate(board_size):
    frame = Frame(frameBottom)
    frame.pack(side=TOP) # create a frame for each row so they are all centered
    for j in range(length):
        letter = board[get_index(row, j)]
        button(frame, letter)
        
update_label()
window.mainloop()