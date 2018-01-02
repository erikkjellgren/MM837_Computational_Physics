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
        
def get_int_auto_corrC(samples):
    deltas = ["1.0", "2.0", "3.0", "4.0", "5.0", "6.0"]
    for j in deltas:
        for i in range(0, samples):
            data = np.genfromtxt("deltaC_"+j+"/int_autocorr_"+str(i)+".dat")
            if i == 0:
                data2 = data
            else:
                data2 += data
        print(np.max(data2/samples), j)
        
def get_int_auto_corr_micro(samples):
    deltas = ["1", "5"]
    for j in deltas:
        for i in range(0, samples):
            data = np.genfromtxt("micro_"+j+"/int_autocorr_"+str(i)+".dat")
            if i == 0:
                data2 = data
            else:
                data2 += data
        print(np.max(data2/samples), j)
        
def get_int_auto_corr_micro20(samples):
    deltas = ["1", "5"]
    for j in deltas:
        for i in range(0, samples):
            data = np.genfromtxt("micro20_"+j+"/int_autocorr_"+str(i)+".dat")
            if i == 0:
                data2 = data
            else:
                data2 += data
        print(np.max(data2/samples), j)
        
def get_int_auto_corr_microC(samples):
    deltas = ["1", "5"]
    for j in deltas:
        for i in range(0, samples):
            data = np.genfromtxt("microC_"+j+"/int_autocorr_"+str(i)+".dat")
            if i == 0:
                data2 = data
            else:
                data2 += data
        print(np.max(data2/samples), j)
        
def get_int_auto_corr_Cluster(samples):
    deltas = ["", "20", "C"]
    for j in deltas:
        for i in range(0, samples):
            data = np.genfromtxt("cluster"+j+"/int_autocorr_"+str(i)+".dat")
            if i == 0:
                data2 = data
            else:
                data2 += data
        print(np.max(data2/samples), j)
        
def plot_two_point_corr(samples):
    for i in range(0, samples):
        data = np.genfromtxt("grnew/two_point_corr_"+str(i)+".dat")
        if i == 0:
            data2 = data
        else:
            data2 += data
        plt.plot(data, '-', linewidth=.5, alpha=.2)
    print(data2/samples)
    plt.plot(data2/samples, 'b-', linewidth=3)
    plt.show()
        
def plot_two_point_corrC(samples):
    for i in range(0, samples):
        data = np.genfromtxt("grC/two_point_corr_"+str(i)+".dat")
        if i == 0:
            data2 = data
        else:
            data2 += data
        plt.plot(data, '.', linewidth=.5, alpha=.2)
    data2 = data2/samples
    print(data2)
    plt.plot(data2, 'b.', linewidth=3)
    plt.show()
    
def plot_two_point_corr20(samples):
    fig = plt.figure()
    ax = fig.add_subplot(111)
    for i in range(0, samples):
        data = np.genfromtxt("gr20/two_point_corr_"+str(i)+".dat")
        if i == 0:
            data2 = data
        else:
            data2 += data
        #plt.plot(data, '.', linewidth=.5, alpha=.2)
    data2 = data2/samples
    x = np.zeros(len(data2))
    for i in range(0, len(x)):
        x[i] = i+1
    ax.set_xlabel('r')
    ax.set_ylabel('G(r)')
    plt.plot(x[0:9], 1.5629*np.exp(-0.376*x[0:9]), 'r--')
    plt.plot(x[0:9], data2[0:9], 'b.', linewidth=3)
    
    
    plt.savefig("twopoint.png")
    
def plot_config():
    data = np.genfromtxt("largeC/lattice_0.dat")
    plt.matshow(data, vmin=-np.pi, vmax=np.pi, cmap=plt.cm.hsv)
    plt.colorbar()
    plt.savefig("largeC.png")
    
def plot_config2():
    data = np.genfromtxt("large/lattice_0.dat")
    plt.matshow(data, vmin=-np.pi, vmax=np.pi, cmap=plt.cm.hsv)
    plt.colorbar()
    plt.savefig("large.png")
    
def plot_config3():
    data = np.genfromtxt("large20/lattice_0.dat")
    plt.matshow(data, vmin=-np.pi, vmax=np.pi, cmap=plt.cm.hsv)
    plt.colorbar()
    plt.savefig("large20.png")
    
    

#plot_energy()
#plot_two_point_corr()
#plot_autocorr(4)
#plot_integrated_autocorr(10)
#get_int_auto_corr(10)
#get_int_auto_corr20(10)
#get_int_auto_corrC(10)
#get_int_auto_corr_micro(10)
#get_int_auto_corr_microC(10)
#get_int_auto_corr_micro20(10)
#get_int_auto_corr_Cluster(10)
plot_two_point_corr20(10)
#plot_config()
#plot_config2()
#plot_config3()