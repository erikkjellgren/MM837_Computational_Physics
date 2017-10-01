/****************************************************************************
 * naive_euler.cc
 * Implements the naive Euler integrator for a single simple harmonic 
 * oscillator. 
 * **************************************************************************/

#include<iostream>
#include<sstream>
#include<vector>
#include "examples.h"
#include "integrators.h"
#include "constraints.h"

using namespace std;
void Euler(int niter, double tau){
	double q0=1, p0=0, E0, Eend; 
	double eps=tau/double(niter);
	vector<double> qn(1,q0), pn(1,p0);
	vector<double> outvec;
	E0 = q0*q0 + p0*p0;
	SimplePendulum sho(1,1); 
	NaiveEulerIntegrator<SimplePendulum, NoConstraints> integrator(sho, NoConstraints(), eps);
	integrator.setInitialConditions(qn,pn); 
	for (int t=0;t<niter;t++) {		
		integrator(qn,pn); 
		cout << qn[0] << ' ' << pn[0] << '\n';
	}
}

int main(){
	Euler(100, 2.0);
}
