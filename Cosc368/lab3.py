from tkinter import *
from tkinter.ttk import * 
import random, time
master = Tk()
c = Canvas(master, width=600, height=300)
c.pack()

class App:

    def __init__(self):
        self.distances = [64, 128, 256, 512]
        self.widths = [8, 16, 32]
        self.repititions = 8
        self.current_combo = 0
        self.index = 0
        self.blue = "left"
        self.get_random_order()
        self.get_rects()
        self.filename = "logWidths.txt"
        self.name = "Jordan"
        self.start_time = time.time()
        master.mainloop()

    def get_random_order(self):
        # create every combination of distance and width, then shuffle
        self.order = []
        for i in range(len(self.distances)):
            for j in range(len(self.widths)):
                self.order.append((self.distances[i], self.widths[j]))
        random.shuffle(self.order)

    def get_margin(self):
        dist, width = self.order[self.index]
        return (600 - (dist + width)) / 2

    def get_rects(self):
        margin = self.get_margin()
        dist, width = self.order[self.index]
        self.right_rect = c.create_rectangle(margin + dist, 0, margin+dist+width, 300, fill="green", tags="green")
        self.left_rect = c.create_rectangle(margin, 0, margin+width, 300, fill="blue")
        c.tag_bind("green", "<ButtonPress-1>", lambda x: self.click())


    def click(self):
        self.current_combo += 1
        if self.current_combo >= self.repititions:
            self.current_combo = 0
            self.index += 1
            if self.index >= len(self.order):
                print("finished")
                self.index = 0
                self.get_random_order()
            c.delete("all")
            self.get_rects()
        
        if self.blue == "left":
            c.itemconfigure(self.left_rect, fill="green", tags="green")
            c.itemconfigure(self.right_rect, fill="blue", tags="blue")
            self.blue = "right"
        else:
            c.itemconfigure(self.left_rect, fill="blue", tags="blue")
            c.itemconfigure(self.right_rect, fill="green", tags="green")
            self.blue = "left"
        time_taken = (time.time() - self.start_time)
        self.log(time_taken)
        self.start_time = time.time()
        
    def log(self, time_taken):
        dist, width = self.order[self.index]
        with open(self.filename, "a+") as f:
            f.write(f"{self.name} {dist} {width} {self.current_combo} {time_taken * 1000}\n")

if __name__ == '__main__':
    App()