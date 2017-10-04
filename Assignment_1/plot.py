import numpy as np
import matplotlib.pyplot as plt

A = np.genfromtxt('out.out')
plt.plot(A[:,0]+A[:,1])
plt.show()