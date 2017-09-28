/****************************************************************************
 * particle_box.cc
 * Compares integrators for many particles in a box.  
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
	
	double eps=tau/double(niter);
	double psize=0.04;

	double Lmax = 2; 

  unsigned seed = 683129629;
	mt19937 gen(seed);
	uniform_real_distribution<double> dist(-Lmax,Lmax);


	//--------------------------------------------------------------------------

	try {

	vector<double> qn(2*nparticles), pn(2*nparticles);

	for (int n = 0; n<qn.size(); ++n) { 
		qn[n] = dist(gen);
		pn[n] = dist(gen);
	}

	HarmonicOscillatorForce gf1(1.0);
	InverseSquareForce gf2(1.0);


	//SquareBox sb(Lmax,psize,2);	
	//PeriodicBox sb(Lmax,2);	
	NoConstraints sb;	
	//UniformForceField cf(1.0,0,2,nparticles);
	//LeapfrogIntegrator<UniformForceField,
	//	NoConstraints> integrator(cf,sb, eps);

	//NoForce gf;
	CentralForce<InverseSquareForce> cf1(gf2,nparticles); 
	CentralForce<HarmonicOscillatorForce> cf3(gf1,nparticles); 
	CentralForce2<HarmonicOscillatorForce> cf2(gf1,nparticles); 

	TwoForces<CentralForce<HarmonicOscillatorForce>,
		CentralForce2<HarmonicOscillatorForce> > cf(cf3,cf2); 

	/*LeapfrogIntegrator<CentralForce2<HarmonicOscillatorForce>,
		NoConstraints> integrator(cf,sb,eps);*/
	
	LeapfrogIntegrator<TwoForces<CentralForce<HarmonicOscillatorForce>,
		CentralForce2<HarmonicOscillatorForce> >,
		NoConstraints> integrator(cf,sb,eps);

	//LeapfrogIntegrator<CentralForce<InverseSquareForce>,
	//	SquareBox> integrator(cf,sb, eps);

	
	integrator.setInitialConditions(qn,pn); 

	double Einit = cf.calcPot(qn);
	for (int i = 0 ; i < pn.size(); ++i)
		Einit += 0.5*pow(pn[i],2);
	
	cout << "Einit = " << Einit<<endl;  

	cout << "force 0 = " << cf(0,qn) << endl;
	double epsd = 1e-5; 
	vector<double> qn_temp=qn;
	qn_temp[0]+=epsd;
	cout << "pot der. 0 = " << (cf.calcPot(qn_temp)-cf.calcPot(qn))/epsd << endl;



	for (int t=0;t<niter;t++) {

		for (int i = 0 ; i < qn.size(); ++i) 
			cout << qn[i] << " " << pn[i] << endl; 

		integrator(qn,pn);

	}
	
	double Efinal =  cf.calcPot(qn);
	for (int i = 0 ; i < pn.size(); ++i)
		Efinal += 0.5*pow(pn[i],2);

	cout << "Efinal = "<<Efinal<<endl;
	cout << "deltaE = "<<Efinal - Einit<<endl;

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
