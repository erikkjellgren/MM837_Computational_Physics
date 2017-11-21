import numpy as np
import matplotlib.pyplot as plt

def plot_wavefunc_sq():
    data1 = np.genfromtxt("phi_sq_1.dat",delimiter=";",skip_header=1)
    data2 = np.genfromtxt("phi_sq_2.dat",delimiter=";",skip_header=1)
    data3 = np.genfromtxt("phi_sq_3.dat",delimiter=";",skip_header=1)
    data4 = np.genfromtxt("phi_sq_4.dat",delimiter=";",skip_header=1)
    
    fig = plt.figure()
    ax = fig.add_subplot(221)
    plt.plot(data1[:,0],data1[:,1],'b-')
    plt.plot([-2,2],[-14.461004,-14.461004],'g-')
    plt.plot(data1[:,0],data1[:,3],'r-')
    
    ax = fig.add_subplot(222)
    plt.plot(data2[:,0],data2[:,1],'b-')
    plt.plot([-2,2],[-9.903720,-9.903720],'g-')
    plt.plot(data2[:,0],data2[:,3],'r-')
    
    ax = fig.add_subplot(223)
    plt.plot(data3[:,0],data3[:,1],'b-')
    plt.plot([-2,2],[-3.095028,-3.095028],'g-')
    plt.plot(data3[:,0],data3[:,3],'r-')
    
    ax = fig.add_subplot(224)
    plt.plot(data4[:,0],data4[:,1],'b-')
    plt.plot([-2,2],[0.087957,0.087957],'g-')
    plt.plot(data4[:,0],data4[:,3],'r-')
    plt.tight_layout()
    
    plt.savefig("sq.pdf")

def plot_wavefunc_tri():
    data1 = np.genfromtxt("phi_tri_1.dat",delimiter=";",skip_header=1)
    data2 = np.genfromtxt("phi_tri_2.dat",delimiter=";",skip_header=1)

    fig = plt.figure()
    ax = fig.add_subplot(211)
    plt.plot(data1[:,0],data1[:,1],'b-')
    plt.plot([-2,2],[-9.568457,-9.568457],'g-')
    plt.plot(data1[:,0],data1[:,3],'r-')
    
    ax = fig.add_subplot(212)
    plt.plot(data2[:,0],data2[:,1],'b-')
    plt.plot([-2,2],[-1.657748,-1.657748],'g-')
    plt.plot(data2[:,0],data2[:,3],'r-')
    plt.tight_layout()
    
    plt.savefig("tri.pdf")
    
def V_a_plot():
    data1 = np.genfromtxt("V.dat")
    data2 = np.genfromtxt("a.dat")

    fig = plt.figure()
    ax = fig.add_subplot(211)
    plt.loglog(data1[:,0],abs(data1[:,1]),'bo', basex=2, basey=2)
    ax.axis([0, 35, 0.0, 32])
    ax.set_ylabel('abs(ground state energy)')
    ax.set_xlabel('k1 (V0)')
    
    ax = fig.add_subplot(212)
    plt.loglog(data2[:,0],abs(data2[:,1]),'bo', basex=2, basey=2)
    ax.axis([0, 17, 4, 16])
    ax.set_ylabel('abs(ground state energy)')
    ax.set_xlabel('k2 (a)')
    plt.tight_layout()
    
    plt.savefig("aV.pdf")
    
def plot_wavefunc():
    data1 = np.genfromtxt("phi.dat",delimiter=";",skip_header=1)
    
    plt.plot(data1[:,0],data1[:,1],'b-')
    plt.plot(data1[:,0],data1[:,3],'r-')
    
    plt.show()
    
#plot_wavefunc_sq()
#plot_wavefunc_tri()
#plot_wavefunc()
V_a_plot()