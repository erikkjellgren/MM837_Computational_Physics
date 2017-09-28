# Simple pendulum animation 

from numpy import sin, cos, pi, array
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from subprocess import *

G =  9.8 # acceleration due to gravity, in m/s^2
L1 = 1.0 # length of pendulum 1 in m
M1 = 1.0 # mass of pendulum 1 in kg

t = "31.4159"
niter = "250"
nmeas = "1"
outfile = "int.dat"
dt = float(t)/float(niter) 

output=check_output( './simple_pendulum '+t+' '+niter+' '+nmeas+' > '+outfile, shell=True) 

fin = open(outfile, 'r'); 

lines=fin.readlines(); 

xdat=[]; ydat=[];

for l in lines:
    temp=l.split();
    xdat.append(float(temp[0]));
    ydat.append(float(temp[1])); 


x1 = L1*sin(xdat[:])
y1 = -L1*cos(xdat[:])

fig = plt.figure()
ax = fig.add_subplot(111, autoscale_on=False, xlim=(-2, 2), ylim=(-2, 2))
ax.grid()

line, = ax.plot([], [], 'o-', lw=2)
time_template = 'time = %.1f'
time_text = ax.text(0.05, 0.9, '', transform=ax.transAxes)

def init():
    line.set_data([], [])
    time_text.set_text('')
    return line, time_text

def animate(i):
    thisx = [0, x1[i]]
    thisy = [0, y1[i]]

    line.set_data(thisx, thisy)
    time_text.set_text(time_template%(i*dt))
    return line, time_text

ani = animation.FuncAnimation(fig, animate, np.arange(1, len(ydat)),
    interval=50, blit=True, init_func=init)

plt.show()
