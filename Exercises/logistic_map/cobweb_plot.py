import matplotlib.pyplot as plt
import numpy as np
from subprocess import *

r = "3.5"
x0 = "0.21"
nmax = "450"
outfile = "cobweb.dat"

output=check_output( 'echo '+r+' '+x0+' '+nmax+' '+outfile+' | ./cobweb.run', shell=True) 

fin = open(outfile, 'r'); 

lines=fin.readlines(); 

xdat=[]; ydat=[];

for l in lines:
    temp=l.split();
    xdat.append(float(temp[0]));
    ydat.append(float(temp[1])); 



#plt.xlabel('n'); plt.ylabel('rel. err.'); 
plt.title('$r = '+r+'$, $x_0 = '+x0+'$'); 
plt.plot(xdat,ydat,'r-',label='$x_{n}$'); 
plt.grid(True);

xmin = min(xdat)
xmax = max(xdat)
rng=xmax-xmin

x = np.linspace(xmin, xmax, 100) 
f0 = x
f1 = float(r)*x*(1-x) 
f2 = float(r)*f1*(1-f1) 
f3 = float(r)*f2*(1-f2) 
f4 = float(r)*f3*(1-f3) 

plt.plot(x,f0,'b--',label='$y=x$'); 
plt.plot(x,f1,'g--',label='$y=f(x)$'); 
plt.plot(x,f4,'y--',label='$y=f^{(4)}(x)$'); 
#plt.legend(fontsize='small')
plt.show() 
