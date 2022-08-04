import numpy as np
import matplotlib.pyplot as plt

from math import sin, cos

NUM_POINTS = 1000

def foo():
    x = np.linspace(-2*np.pi, 2*np.pi, NUM_POINTS)
    y = np.sin(x) / x
    axes = plt.axes()
    axes.plot(x, y)

    axes.grid(True)
    plt.show()

def derivative(f, x, h=1e-12):
    return (f(x + h) - f(x)) / h

def newtons_method(f, x0, tol=0.5e-6, max_iter=1000):
    x = x0
    delta = np.inf
    
    i = 0
    guesses = [x]
    while i < max_iter and delta >= 0.5e-6:
        i += 1
        x_prev = x
        x -= f(x) / derivative(f, x)
        delta = np.abs(x - x_prev)
        guesses.append(x)

    
    return x, np.array(guesses)
f = lambda x: (x*cos(x) - sin(x))/(x*x)
root, guesses = newtons_method(f, 3)
print(f'root = {root:.6f}')

foo()