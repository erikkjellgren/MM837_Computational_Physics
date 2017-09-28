/****************************************************************************
 * int_test2.cc
 * Compares integrators for a single simple harmonic 
 * oscillator. 
 * **************************************************************************/

#include<iostream>
#include<sstream>
#include "examples.h"
#include "integrators.h"

using namespace std;

int main(int argc, char** argv) {

	if (argc != 4) {
		cerr << "usage: " << argv[0] <<" <t> <niter> <nmeas> " << endl;
		return 1;
	}

	
	double tau; stringstream(argv[1]) >> tau;  //The length of the traj. 
	int niter; stringstream(argv[2]) >> niter;  //The number of steps in a traj. 
	int nmeas; stringstream(argv[3]) >> nmeas;  //The number of steps in a traj. 
	
	double q0=1, p0=0; 
	double dn = 10;
	int nn = 500; 

	//--------------------------------------------------------------------------

	for (int i=0; i<nn; i++) {   

		double eps=tau/double(niter);
		vector<double> qn(1,q0), pn(1,p0);

		SimpleHarmonicOscillator sho(1,1); 
		RK4Integrator<SimpleHarmonicOscillator> integrator(sho, eps);
	//	EulerCromerIntegrator<SimpleHarmonicOscillator> integrator(sho, eps);
	//RK2Integrator<SimpleHarmonicOscillator> integrator(sho, eps);
//	LeapfrogIntegrator<SimpleHarmonicOscillator> integrator(sho, eps);

		integrator.setInitialConditions(qn,pn); 

		for (int t=0;t<niter;t++) {


			integrator(qn,pn); 
		}

		cout << eps << "   " << 0.5*(qn[0]*qn[0] + pn[0]*pn[0]) - 0.5 << endl; 
		niter += dn; 
	}
	
	return 0;
}
