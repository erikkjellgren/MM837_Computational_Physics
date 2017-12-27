import matplotlib.pyplot as plt
import numpy as np

def plot_energy():
    for i in range(0, 1):
        data = np.genfromtxt("energy_"+str(i)+".dat")
        plt.plot(data,'-')
    plt.show()

def plot_integrated_autocorr(samples):
    for i in range(0, samples):
        data = np.genfromtxt("delta_1.0/int_autocorr_"+str(i)+".dat")
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

def get_int_auto_corr(samples):
    deltas = ["1.0", "1.5", "2.0", "2.5", "3.0", "3.5", "4.0", "4.5", "5.0", "5.5", "6.0"]
    for j in deltas:
        for i in range(0, samples):
            data = np.genfromtxt("delta_"+j+"/int_autocorr_"+str(i)+".dat")
            if i == 0:
                data2 = data
            else:
                data2 += data
        print(np.max(data2/samples), j)
        
def get_int_auto_corr20(samples):
    deltas = ["0.25", "0.5", "0.75", "1.0", "1.25", "1.5", "1.75", "2.0"]
    for j in deltas:
        for i in range(0, samples):
            data = np.genfromtxt("delta20_"+j+"/int_autocorr_"+str(i)+".dat")
            if i == 0:
                data2 = data
            else:
                data2 += data
        print(np.max(data2/samples), j)

#plot_energy()
#plot_two_point_corr()
#plot_autocorr(4)
#plot_integrated_autocorr(10)
#animate_lattice()
#get_int_auto_corr(10)
get_int_auto_corr20(10)