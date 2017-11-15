import numpy as np
import matplotlib.pyplot as plt

def plot_wavefunc():
    data = np.genfromtxt("phi.dat",delimiter=";",skip_header=1)
    plt.plot(data[:,0],data[:,1],'b-')
    plt.plot(data[:,0],data[:,3],'r-')
    plt.show()

plot_wavefunc()