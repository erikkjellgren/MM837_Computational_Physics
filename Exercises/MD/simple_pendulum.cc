/****************************************************************************
 * int_test.cc
 * Compares integrators for a single simple pendulum 
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
	double eps=tau/double(niter);
	//--------------------------------------------------------------------------

	vector<double> qn(1,q0), pn(1,p0);

	SimplePendulum sp(1,9.8,1); 
	LeapfrogIntegrator<SimplePendulum> integrator(sp, eps);

	for (int t=0;t<niter;t++) {

		vector<double> qnp1(1); 
		vector<double> pnp1(1); 

		integrator(qn,pn,qnp1,pnp1); 

		if ((t % nmeas)==0) 
			cout << qn[0] << " " << pn[0] << endl; 

		qn = qnp1; 
		pn = pnp1; 

	}

	return 0;

}
