import matplotlib.pyplot as plt
import numpy as np

def plot_energy():
    for i in range(0, 1):
        data = np.genfromtxt("energy_"+str(i)+".dat")
        plt.plot(data,'-')
    plt.show()

def plot_integrated_autocorr(samples):
    for i in range(0, samples):
        data = np.genfromtxt("int_autocorr_"+str(i)+".dat")
        if i == 0:
            data2 = data
        else:
            data2 += data
        plt.plot(data, '-', linewidth=.5, alpha=.2)
    plt.plot(data2/samples, 'b-', linewidth=3)
    plt.show()
    
def plot_autocorr(samples):
    for i in range(0, samples):
        data = np.genfromtxt("autocorr_"+str(i)+".dat")
        if i == 0:
            data2 = data
        else:
            data2 += data
        plt.plot(data, '-', linewidth=.5, alpha=.2)
    plt.plot(data2/samples, 'b-', linewidth=3)
    plt.show()
    
def plot_two_point_corr():
    data = np.genfromtxt("two_point_corr_0.dat")
    plt.plot(data)
    plt.show()


#plot_energy()
#plot_two_point_corr()
#plot_autocorr(4)
plot_integrated_autocorr(4)
#animate_lattice()