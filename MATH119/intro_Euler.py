import numpy as np
import matplotlib.pyplot as plt


def main(fname, func):
    """Perform several iterations of Euler's method"""
    # y0 = float(input("What initial condition do you want to use? "))
    y0 = 1
    # h = float(input("What stepsize do you want to use? "))
    h=0.01
    # total_steps = int(input("final t: "))
       # made this an f string to display h value
    
    t0 = 0
    # total_steps -= t0

    # total_steps /= h
    total_steps = 2/h
    x_vals = [0]
    y_vals = [y0]

    
    this_step = 0
    while this_step <= total_steps:
        t0,y0 = Euler_step(fname,t0,y0,h)
        x_vals.append(t0)
        y_vals.append(y0)
        this_step += 1
    
    axes = plt.axes()
    axes.plot(x_vals, y_vals, label="approx")

    x_vals = np.arange(0, 2, h)
    y_vals = func(x_vals)
    # axes.plot(x_vals, y_vals, label="exact")

    axes.grid()
    axes.legend()
    plt.show()


def Euler_step(fname,t0,y0,timestep,quiet='no'):
    """One step of Euler's method"""
    f = fname(t0,y0)
    y1 = np.add(y0,timestep*f)
    t1 = t0 + timestep
    
    if quiet == 'no':
        print("t = {:.2f}  |  y = {}  |  f(t,y) = {}  |  h x f(t,y) = {}  | y_new = {}".format(t0,np.around(y0,decimals=4),
        np.around(f,decimals=4),np.around(timestep*f,decimals=4),np.around(y1,decimals=4))) 

    return t1,y1

    

def de_rhs_emth119_ex1(t,y):
    """Evaluates RHS of a differential equation"""
    f = 1 - 0.5 * t * y
    return(f)

def de_rhs_emth119_ex2(t,y):
    """Evaluates RHS of a differential equation"""
    f = y + t
    return(f)

def de_rhs_exp_rate1(t,y):
    """Evaluates RHS of a differential equation for exponential growth"""
    f = y
    return(f)
    
    
# t = 0
# y = 0
# t,y = Euler_step(de_rhs_emth119_ex1,t,y,1)
#
# OR 
# 
# main(de_rhs_emth119_ex1) 0 1 3
# main(de_rhs_emth119_ex2) 1 0.1 5
# main(de_rhs_exp_rate1) 1 1 1    1 0.5 2    1 0.25 4

# main(de_rhs_emth119_ex1)
approx = lambda t, y: 3+np.exp(-t)-1/2*y
exact = lambda x: 1/2-1/2*np.exp(-x)+np.exp(-x/2)
main(approx, exact)

