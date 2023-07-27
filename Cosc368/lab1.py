from tkinter import *
from tkinter.ttk import * 
window = Tk()

board = ['qwertyuiop', 'asdfghjkl', 'zxcvbnm']


frameBottom = Frame(window, borderwidth=1, relief="solid", padding=10)
frameBottom.pack(side=BOTTOM, padx=10, pady=10)

frameTop = Frame(window)
frameTop.pack(side=TOP, fill=X, padx=10, pady=10)

label = Label(frameTop)
label.pack(side=LEFT)

clearBtn = Button(frameTop, text="Clear", command=lambda: label.config(text=''))
clearBtn.pack(side=RIGHT)

def append(letter):
    label['text'] += letter

for i, row in enumerate(board):
    frame = Frame(frameBottom)
    frame.pack(side=TOP)
    for j, letter in enumerate(row):
        btn = Button(frame, text=letter, command=lambda letter=letter: append(letter), width=5)
        btn.pack(side=LEFT)
        

window.mainloop()