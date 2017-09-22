import matplotlib.pyplot as plt
import numpy as np
from subprocess import *

rmin = "2.5"
rmax = "4"
nr = "2000"
x0 = "0.2"
nmin = "500"
nmax = "600"
outfile = "bif.dat"

output=check_output( 'echo '+rmin+' '+rmax+' '+nr+' '+x0+' '+nmin+' '+nmax+' '+outfile+' | ./bifurcation.run', shell=True) 

fin = open(outfile, 'r'); 

lines=fin.readlines(); 

xdat=[]; ydat=[];

for l in lines:
    temp=l.split();
    xdat.append(float(temp[0]));
    ydat.append(float(temp[1])); 


plt.xlabel('$r$'); plt.ylabel('$x^{*}$'); 
plt.title('Bifurcation diagram'); 
plt.plot(xdat,ydat,'bo',markersize=1); 
plt.grid(True);
plt.show() 
