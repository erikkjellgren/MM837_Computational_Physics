import numpy as np
import matplotlib.pyplot as plt

def plot_energy():
    for i in range(3, 4):
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
    
def plot_histogram():
    for i in range(0, 4):
        if i == 0:
            data = np.genfromtxt("energy_"+str(i)+".dat")
        else:
            data2 = np.genfromtxt("energy_"+str(i)+".dat")
            data = np.concatenate((data, data2))
    plt.hist(data, bins=100)
    plt.show()
    
def get_time():
    for j in range(0, 6):
        for i in range(0, 100):
            data = np.genfromtxt("hybrid_"+str(j)+"/int_autocorr_"+str(i)+".dat")
            if i == 0:
                data2 = data
            else:
                data2 += data
        print(np.max(data2/100))
        
def plot_autocorr_all():
    fig = plt.figure()
    ax = fig.add_subplot(221)
    for i in range(0, 100):
        data = np.genfromtxt("q2_typewriter/autocorr_"+str(i)+".dat")
        if i == 0:
            data2 = data
        else:
            data2 += data
        plt.plot(data, '-', linewidth=.5, alpha=.2)
    plt.title('q=2, Typewriter')
    plt.plot(data2/100, 'b-', linewidth=3)
    
    ax = fig.add_subplot(222)
    for i in range(0, 100):
        data = np.genfromtxt("q2_cluster/autocorr_"+str(i)+".dat")
        if i == 0:
            data2 = data
        else:
            data2 += data
        plt.plot(data, '-', linewidth=.5, alpha=.2)
    plt.title('q=2, Cluster')
    plt.plot(data2/100, 'b-', linewidth=3)
    
    ax = fig.add_subplot(223)
    for i in range(0, 100):
        data = np.genfromtxt("q20_typewriter/autocorr_"+str(i)+".dat")
        if i == 0:
            data2 = data
        else:
            data2 += data
        plt.plot(data, '-', linewidth=.5, alpha=.2)
    plt.title('q=20, Typewriter')
    plt.plot(data2/100, 'b-', linewidth=3)
    
    ax = fig.add_subplot(224)
    for i in range(0, 100):
        data = np.genfromtxt("q20_cluster/autocorr_"+str(i)+".dat")
        if i == 0:
            data2 = data
        else:
            data2 += data
        plt.plot(data, '-', linewidth=.5, alpha=.2)
    plt.title('q=20, Cluster')
    plt.plot(data2/100, 'b-', linewidth=3)
    
    plt.tight_layout()
    plt.savefig("autocorr.pdf")
    
def plot_int_autocorr_all():
    fig = plt.figure()
    ax = fig.add_subplot(221)
    for i in range(0, 100):
        data = np.genfromtxt("q2_typewriter/int_autocorr_"+str(i)+".dat")
        if i == 0:
            data2 = data
        else:
            data2 += data
        plt.plot(data, '-', linewidth=.5, alpha=.2)
    plt.title('q=2, Typewriter')
    plt.plot(data2/100, 'b-', linewidth=3)
    print(np.max(data2/100))
    
    ax = fig.add_subplot(222)
    for i in range(0, 100):
        data = np.genfromtxt("q2_cluster/int_autocorr_"+str(i)+".dat")
        if i == 0:
            data2 = data
        else:
            data2 += data
        plt.plot(data, '-', linewidth=.5, alpha=.2)
    plt.title('q=2, Cluster')
    plt.plot(data2/100, 'b-', linewidth=3)
    print(np.max(data2/100))
    
    ax = fig.add_subplot(223)
    for i in range(0, 100):
        data = np.genfromtxt("q20_typewriter/int_autocorr_"+str(i)+".dat")
        if i == 0:
            data2 = data*100
        else:
            data2 += data*100
        plt.plot(data*100, '-', linewidth=.5, alpha=.2)
    plt.title('q=20, Typewriter')
    plt.plot(data2/100, 'b-', linewidth=3)
    print(np.max(data2/100))
    
    ax = fig.add_subplot(224)
    for i in range(0, 100):
        data = np.genfromtxt("q20_cluster/int_autocorr_"+str(i)+".dat")
        if i == 0:
            data2 = data*100
        else:
            data2 += data*100
        plt.plot(data*100, '-', linewidth=.5, alpha=.2)
    plt.title('q=20, Cluster')
    plt.plot(data2/100, 'b-', linewidth=3)
    print(np.max(data2/100))
    
    plt.tight_layout()
    plt.savefig("int_autocorr.pdf")
    
def plot_histogram_all():
    fig = plt.figure()
    ax = fig.add_subplot(211)
    for i in range(0, 4):
        if i == 0:
            data = np.genfromtxt("q2_hist/energy_"+str(i)+".dat")
        else:
            data2 = np.genfromtxt("q2_hist/energy_"+str(i)+".dat")
            data = np.concatenate((data, data2))
    plt.hist(data, bins=118)
    plt.title('q=2, Typewriter')
    
    ax = fig.add_subplot(212)
    for i in range(0, 4):
        if i == 0:
            data = np.genfromtxt("q20_hist/energy_"+str(i)+".dat")
        else:
            data2 = np.genfromtxt("q20_hist/energy_"+str(i)+".dat")
            data = np.concatenate((data, data2))
    plt.hist(data, bins=59)
    plt.title('q=20, Typewriter')
    
    plt.tight_layout()
    plt.savefig("histograms.pdf")
    
    
def plot_energies_all():
    fig = plt.figure()
    ax = fig.add_subplot(211)
    data = np.genfromtxt("q2_hist/energy_3.dat")
    plt.plot(data)
    plt.title('q=2, Typewriter')
    
    ax = fig.add_subplot(212)
    data = np.genfromtxt("q20_hist/energy_3.dat")
    plt.plot(data)
    plt.title('q=20, Typewriter')
    
    plt.tight_layout()
    plt.savefig("energies.pdf")

    
#plot_energy()
plot_integrated_autocorr(100)
#plot_autocorr(samples)
#plot_histogram()
#get_time()
#plot_autocorr_all()
#plot_int_autocorr_all()
#plot_histogram_all()
#plot_energies_all()