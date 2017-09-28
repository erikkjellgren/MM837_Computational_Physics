import matplotlib.pyplot as plt
import numpy as np
from subprocess import *

t = "90"
niter = "500"
nmeas = "1"
outfile = "int.dat"

#output=check_output( './naive_euler '+t+' '+niter+' '+nmeas+' > '+outfile, shell=True) 
#output=check_output( './euler_cromer '+t+' '+niter+' '+nmeas+' > '+outfile, shell=True) 
#output=check_output( './leapfrog '+t+' '+niter+' '+nmeas+' > '+outfile, shell=True) 
#output=check_output( './rk2 '+t+' '+niter+' '+nmeas+' > '+outfile, shell=True) 
#output=check_output( './rk4 '+t+' '+niter+' '+nmeas+' > '+outfile, shell=True) 

fin = open(outfile, 'r'); 

lines=fin.readlines(); 

state[][][];

for l in lines:
    temp=l.split();
    q=float(temp[0]) 
    p=float(temp[1]) 

    #xdat.append(q*q+p*p);
    xdat.append(float(temp[0])); 
    #xdat.append(float(temp[0])**4); 
    ydat.append(float(temp[1])); 



#plt.xlabel('n'); plt.ylabel('rel. err.'); 
#plt.title('$r = '+r+'$, $x_0 = '+x0+'$'); 
#plt.plot(xdat,'r-',label='$x_{n}$'); 
plt.plot(xdat,ydat,'r-',label='$x_{n}$'); 
plt.grid(True);

plt.show() 
