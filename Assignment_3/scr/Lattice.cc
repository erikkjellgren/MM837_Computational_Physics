/*****************************************************************************
 * Lattice.cc
 * Container for lattice information
 * ***************************************************************************/

#include<vector>
#include<random>
#include"Lattice.h"
 
using namespace std;

template<class Sweeper>
Lattice<Sweeper>::Lattice(const Sweeper& Sweep_in, const int& seed_in, const int& L_in, const int& q_in) : 
	Sweep(Sweep_in), seed(seed_in), L(L_in), q(q_in){
	
	mt19937 gen(seed);
	uniform_int_distribution<int> uniform_int_random(1,q);
	
	// build lattice
	vector<vector<int>> lattice(L,vector<int>(L,0));
	for (int i=0; i<L; i++){
		for (int j=0; j<L; j++){
			lattice[i][j] = uniform_int_random(gen);
		}
	}
}

template<class Sweeper>
void Lattice<Sweeper>::do_sweep(){
	 Sweep(lattice, Delta_Energy);
	 Energy += Delta_Energy;
}

template<class Sweeper>
double Lattice<Sweeper>::return_energy(){
	return Energy;
}
