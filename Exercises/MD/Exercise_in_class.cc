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
vector<double> Euler(int niter, double tau){
	double q0=1, p0=0, E0, Eend; 
	double eps=tau/double(niter);
	vector<double> qn(1,q0), pn(1,p0);
	vector<double> outvec;
	E0 = q0*q0 + p0*p0;
	SimpleHarmonicOscillator sho(1,1); 
	NaiveEulerIntegrator<SimpleHarmonicOscillator, NoConstraints> integrator(sho, NoConstraints(), eps);
	integrator.setInitialConditions(qn,pn); 
	for (int t=0;t<niter;t++) {		
		integrator(qn,pn); 
	}
	Eend = qn[0]*qn[0] + pn[0]*pn[0];
	outvec.push_back(Eend - E0);
	outvec.push_back(eps);
	return outvec;
}

int main(){
	double tau = 100;
	int niter;
	vector<double> output;
	
	for (int i=1;i<9;i++){
		output = Euler(i*100, 2.0);
		cout << output[0] << ' ' << output[1] << '\n';
	}
	
	
}