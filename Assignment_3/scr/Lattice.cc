/*****************************************************************************
 * Lattice.cc
 * Container for operations done on the lattice
 * ***************************************************************************/

#include<vector>
#include<random>
#include"Lattice.h"
 
using namespace std;

Lattice::Lattice(const int& seed_in, const int& L_in, const int& q_in, const double& beta_in, const int& sweeping_method_in) : 
	seed(seed_in), L(L_in), q(q_in), beta(beta_in), sweeping_method(sweeping_method_in){
	
	mt19937 gen(seed);
	uniform_real_distribution<double> uniform_random(0,1);
	uniform_int_distribution<int> uniform_int_random(1,q);
	if (sweeping_method == 1){
		Sweep = &Lattice::Typewriter;
	}
	
	// build lattice
	vector<vector<int>> lattice(L,vector<int>(L,0));
	for (int i=0; i<L; i++){
		for (int j=0; j<L; j++){
			lattice[i][j] = uniform_int_random(gen);
		}
	}
}

void Lattice::do_sweep(){
	 (this->*Sweep)();
	 Energy += Delta_Energy_total;
}

double Lattice::return_energy(){
	return Energy;
}

void Lattice::Typewriter(){
	
	Delta_Energy_total = 0;

	// upperleft corner
	local_energy = reverse_delta_function(lattice[0][0],lattice[0][L-1])
				+ reverse_delta_function(lattice[0][0],lattice[L-1][0])
				+ reverse_delta_function(lattice[0][0],lattice[0][1])
				+ reverse_delta_function(lattice[0][0],lattice[1][0]);
	purposal = uniform_int_random(gen);
	Delta_Energy = reverse_delta_function(purposal,lattice[0][L-1])
				+ reverse_delta_function(purposal,lattice[L-1][0])
				+ reverse_delta_function(purposal,lattice[0][1])
				+ reverse_delta_function(purposal,lattice[1][0])
				- local_energy;
	check_purposal(0, 0);

	
	// upperright corner
	local_energy = reverse_delta_function(lattice[0][L-1],lattice[0][0])
				+ reverse_delta_function(lattice[0][L-1],lattice[L-1][L-1])
				+ reverse_delta_function(lattice[0][L-1],lattice[0][L-2])
				+ reverse_delta_function(lattice[0][L-1],lattice[1][L-1]);
	purposal = uniform_int_random(gen);
	Delta_Energy = reverse_delta_function(purposal,lattice[0][0])
				+ reverse_delta_function(purposal,lattice[L-1][L-1])
				+ reverse_delta_function(purposal,lattice[0][L-2])
				+ reverse_delta_function(purposal,lattice[1][L-1])
				- local_energy;
	check_purposal(0, L-1);
	
	// lowerleft corner
	local_energy = reverse_delta_function(lattice[L-1][0],lattice[0][0])
				+ reverse_delta_function(lattice[L-1][0],lattice[L-1][L-1])
				+ reverse_delta_function(lattice[L-1][0],lattice[L-2][0])
				+ reverse_delta_function(lattice[L-1][0],lattice[L-1][1]);
	purposal = uniform_int_random(gen);
	Delta_Energy = reverse_delta_function(purposal,lattice[0][0])
				+ reverse_delta_function(purposal,lattice[L-1][L-1])
				+ reverse_delta_function(purposal,lattice[L-2][0])
				+ reverse_delta_function(purposal,lattice[L-1][1])
				- local_energy;
	check_purposal(L-1, 0);
	
	// lowerright corner
	local_energy = reverse_delta_function(lattice[L-1][L-1],lattice[L-1][0])
				+ reverse_delta_function(lattice[L-1][L-1],lattice[0][L-1])
				+ reverse_delta_function(lattice[L-1][L-1],lattice[L-2][L-1])
				+ reverse_delta_function(lattice[L-1][L-1],lattice[L-1][L-2]);
	purposal = uniform_int_random(gen);
	Delta_Energy = reverse_delta_function(lattice[L-1][L-1],lattice[L-1][0])
				+ reverse_delta_function(lattice[L-1][L-1],lattice[0][L-1])
				+ reverse_delta_function(lattice[L-1][L-1],lattice[L-2][L-1])
				+ reverse_delta_function(lattice[L-1][L-1],lattice[L-1][L-2])
				- local_energy;
	check_purposal(L-1, L-1);
	
	// Do top
	for (int j=1; j<L-1; j++){
		local_energy = reverse_delta_function(lattice[0][j],lattice[L-1][j])
					+ reverse_delta_function(lattice[0][j],lattice[0][j-1])
					+ reverse_delta_function(lattice[0][j],lattice[0][j+1])
					+ reverse_delta_function(lattice[0][j],lattice[1][j]);
		purposal = uniform_int_random(gen);
		Delta_Energy = reverse_delta_function(purposal,lattice[L-1][j])
					+ reverse_delta_function(purposal,lattice[0][j-1])
					+ reverse_delta_function(purposal,lattice[0][j+1])
					+ reverse_delta_function(purposal,lattice[1][j])
					- local_energy;
		check_purposal(0, j);
	}
	// Do bottom
	for (int j=1; j<L-1; j++){
		local_energy = reverse_delta_function(lattice[L-1][j],lattice[0][j])
					+ reverse_delta_function(lattice[L-1][j],lattice[L-1][j-1])
					+ reverse_delta_function(lattice[L-1][j],lattice[L-1][j+1])
					+ reverse_delta_function(lattice[L-1][j],lattice[L-2][j]);
		purposal = uniform_int_random(gen);
		Delta_Energy = reverse_delta_function(purposal,lattice[0][j])
					+ reverse_delta_function(purposal,lattice[L-1][j-1])
					+ reverse_delta_function(purposal,lattice[L-1][j+1])
					+ reverse_delta_function(purposal,lattice[L-2][j]);
					- local_energy;
		check_purposal(L-1, j);
	}
	// Do left
	for (int i=1; i<L-1; i++){
		local_energy = reverse_delta_function(lattice[i][0],lattice[i][L-1])
					+ reverse_delta_function(lattice[i][0],lattice[i-1][0])
					+ reverse_delta_function(lattice[i][0],lattice[i+1][0])
					+ reverse_delta_function(lattice[i][0],lattice[i][1]);
		purposal = uniform_int_random(gen);
		Delta_Energy = reverse_delta_function(purposal,lattice[i][L-1])
					+ reverse_delta_function(purposal,lattice[i-1][0])
					+ reverse_delta_function(purposal,lattice[i+1][0])
					+ reverse_delta_function(purposal,lattice[i][1])
					- local_energy;
		check_purposal(i, 0);
					
	}			
	// Do right
	for (int i=1; i<L-1; i++){
		local_energy = reverse_delta_function(lattice[i][L-1],lattice[i][0])
					+ reverse_delta_function(lattice[i][L-1],lattice[i-1][L-1])
					+ reverse_delta_function(lattice[i][L-1],lattice[i+1][L-1])
					+ reverse_delta_function(lattice[i][L-1],lattice[i][L-2]);
		purposal = uniform_int_random(gen);
		Delta_Energy = reverse_delta_function(lattice[i][L-1],lattice[i][0])
					+ reverse_delta_function(lattice[i][L-1],lattice[i-1][L-1])
					+ reverse_delta_function(lattice[i][L-1],lattice[i+1][L-1])
					+ reverse_delta_function(lattice[i][L-1],lattice[i][L-2])
					- local_energy;
		check_purposal(i, L-1);
	}	
	
	// Do middle
	for (int i=1; i<L-1; i++){
		for (int j=1; j<L-1; j++){
			local_energy = reverse_delta_function(lattice[i][j],lattice[i-1][j])
					+ reverse_delta_function(lattice[i][j],lattice[i+1][j])
					+ reverse_delta_function(lattice[i][j],lattice[i][j-1])
					+ reverse_delta_function(lattice[i][j],lattice[i][j+1]);
		purposal = uniform_int_random(gen);
		Delta_Energy = reverse_delta_function(lattice[i][j],lattice[i-1][j])
					+ reverse_delta_function(lattice[i][j],lattice[i+1][j])
					+ reverse_delta_function(lattice[i][j],lattice[i][j-1])
					+ reverse_delta_function(lattice[i][j],lattice[i][j+1])
					- local_energy;
		check_purposal(i, j);
		}
	}
}


int Lattice::reverse_delta_function(const int& spin_i, const int& spin_j){
	int output;
	if (spin_i == spin_j){output=0;}
	else {output=1;}
	return output;
}

void Lattice::check_purposal(const int& spin_i, const int& spin_j){
	p_accept = exp(-beta*(double)(Delta_Energy));
	if (p_accept >= 1.0){
		lattice[spin_i][spin_j] = purposal;
		Delta_Energy_total += Delta_Energy;
	}
	else if (p_accept > uniform_random(gen)){
		lattice[spin_i][spin_j] = purposal;
		Delta_Energy_total += Delta_Energy;
	}
}
