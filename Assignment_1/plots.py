import numpy as np
import matplotlib.pyplot as plt

def velocityhistogram():
    data = np.genfromtxt("velocitydistribution.dat",skip_header=1,skip_footer=1)
    plt.hist(data[:,0]**2,len(data), weights=data[:,1],linewidth=0)
    plt.show()

def plot_energy():
    data = np.genfromtxt("energy.dat",skip_header=1)
    plt.plot(data[:,0],data[:,1]+data[:,2])
    plt.show()

velocityhistogram()
#plot_energy()