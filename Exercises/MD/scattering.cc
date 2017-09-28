/****************************************************************************
 * scattering.cc
 * Compares integrators two particles scattering in a box.  
 * **************************************************************************/

#include<iostream>
#include<sstream>
#include<random>
#include "examples.h"
#include "integrators.h"
#include "constraints.h"

using namespace std;

int main(int argc, char** argv) {

	if (argc != 4) {
		cerr << "usage: " << argv[0] <<" <t> <niter> <npart> " << endl;
		return 1;
	}

	
	double tau; stringstream(argv[1]) >> tau;  //The length of the traj. 
	int niter; stringstream(argv[2]) >> niter;  //The number of steps in a traj. 
	int nparticles; stringstream(argv[3]) >> nparticles;  //The number of steps in a traj. 

	nparticles = 2;
	double eps=tau/double(niter);
	double psize=0.04;

	double Lmax = 2; 

  unsigned seed = 683129629;
	mt19937 gen(seed);
	uniform_real_distribution<double> dist(-Lmax,Lmax);

	double h = 0.2; 

	//--------------------------------------------------------------------------

	try {

	vector<double> qn(2*nparticles), pn(2*nparticles);

	qn[0] = -0.5; 
	qn[1] = h; 
	qn[2] = -qn[0]; 
	qn[3]=-h; 

	pn[0] = 1.0;
	pn[1]=0.0;
	pn[2]=-1.0; 
	pn[3]=0.0;
	
	InverseSquareForce gf(1.0);
//NoForce gf;
// UniformForceField gf(-10, 1, 2,nparticles);
	SquareBox sb(Lmax,psize,2);	
  //CentralForce<NoForce> cf(gf,nparticles); 
	CentralForce<InverseSquareForce> cf(gf, nparticles); 
	
//LeapfrogIntegrator<CentralForce<NoForce>,
	//	SquareBox> integrator(cf,sb, eps);
	
	LeapfrogIntegrator<CentralForce<InverseSquareForce>,
		SquareBox> integrator(cf,sb, eps);

	
	integrator.setInitialConditions(qn,pn); 

	for (int t=0;t<niter;t++) {

		for (int i = 0 ; i < qn.size(); ++i) 
			cout << qn[i] << " " << pn[i] << endl; 

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
