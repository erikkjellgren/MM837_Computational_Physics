/****************************************************************************
 * naive_euler.cc
 * Implements the naive Euler integrator for a single simple harmonic 
 * oscillator. 
 * **************************************************************************/

#include<iostream>
#include<sstream>

using namespace std;

int main(int argc, char** argv) {

	if (argc != 4) {
		cerr << "usage: " << argv[0] <<" <t> <niter> <nmeas> " << endl;
		return 1;
	}

	
	double tau; stringstream(argv[1]) >> tau;  //The length of the traj. 
	int niter; stringstream(argv[2]) >> niter;  //The number of steps in a traj. 
	int nmeas; stringstream(argv[3]) >> nmeas;  //The number of steps in a traj. 
	
	double x0=1, p0=0; 
	double eps=tau/double(niter);
	//--------------------------------------------------------------------------

	double xn=x0, pn=p0;
 
	for (int t=0;t<niter;t++) {

		if ((t % nmeas)==0) 
			cout << xn << " " << pn << endl;  

		double xnp1 = xn + eps*pn;
		double pnp1 = pn - eps*xn;

		xn = xnp1; 
		pn = pnp1; 

	}

	return 0;

}
