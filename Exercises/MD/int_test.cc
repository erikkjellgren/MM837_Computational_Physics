/****************************************************************************
 * int_test.cc
 * Compares integrators for a single simple harmonic 
 * oscillator. 
 * **************************************************************************/

#include<iostream>
#include<sstream>
#include "examples.h"
#include "integrators.h"
#include "constraints.h"

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
	double eps=tau/double(niter);
	//--------------------------------------------------------------------------

	try {

	vector<double> qn(1,q0), pn(1,p0);

	SimpleHarmonicOscillator sho(1,1); 
	NaiveEulerIntegrator<SimpleHarmonicOscillator, NoConstraints> integrator(sho, NoConstraints(), eps);

	integrator.setInitialConditions(qn,pn); 

	for (int t=0;t<niter;t++) {

		if ((t % nmeas)==0) 
			cout << qn[0] << " " << pn[0] << endl; 
		
		integrator(qn,pn); 
	}

} catch (const invalid_argument& e) {
    cerr << "Invalid argument: "<< e.what() << endl;
		return 1;
}
 catch (const logic_error& e) {
    cerr << "Logic Error: "<< e.what() << endl;
		return 2;
}
	return 0;

}
