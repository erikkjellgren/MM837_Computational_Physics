import numpy as np
import matplotlib.pyplot as plt

def plot_energy():
    data = np.genfromtxt("energy.dat")
    plt.plot(data)
    plt.show()

def plot_integrated_autocorr():
    data = np.genfromtxt("autocorr.dat")
    plt.plot(data)
    plt.show()
    
#plot_energy()
plot_integrated_autocorr()