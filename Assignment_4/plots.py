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

def animate_lattice():
    L = 20
    
    plt.ion()
    fig = plt.figure()
    ax = fig.add_subplot(111)
    data = np.genfromtxt("lattice_0.dat")
    x = np.cos(data[0:L,:])
    y = np.sin(data[0:L,:])
    m = ax.matshow(data[0:L,:], vmin=-np.pi, vmax=np.pi, cmap=plt.cm.hsv)
    q = ax.quiver(x,y)
    #plt.colorbar()
    
    for j in range(1, int(len(data)/L)):
        data_new = data[j*L:(j+1)*L,:]
        x = np.cos(data_new)
        y = np.sin(data_new)
        m.set_data(data_new)
        q.U = x.flat[:]
        q.V = y.flat[:]
        plt.pause(0.00001)

plot_energy()
#plot_autocorr(1)
#plot_integrated_autocorr(1)
#animate_lattice()