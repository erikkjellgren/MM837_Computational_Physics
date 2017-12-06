import numpy as np
import matplotlib.pyplot as plt

def plot_energy():
    data = np.genfromtxt("energy_0.dat")
    plt.plot(data)
    plt.show()

def plot_integrated_autocorr():
    data = np.genfromtxt("int_autocorr_0.dat")
    plt.plot(data)
    plt.show()
    
def plot_autocorr():
    for i in range(0, 20):
        data = np.genfromtxt("autocorr_"+str(i)+".dat")
        plt.plot(data)
    plt.show()
    
#plot_energy()
#plot_integrated_autocorr()
plot_autocorr()