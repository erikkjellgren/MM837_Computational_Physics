import numpy as np
import matplotlib.pyplot as plt

A = np.genfromtxt('out.out')
B = np.genfromtxt('parallel/out.out')
plt.plot(A[:,0]+A[:,1]-(B[:,0]+B[:,1]))
plt.show()