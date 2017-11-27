/*****************************************************************************
 * Lattice.cc
 * Container for operations done on the lattice
 * ***************************************************************************/

#include<vector>
#include<random>
#include<iostream>
#include"Lattice.h"
 
using namespace std;

Lattice::Lattice(const int& seed_in, const int& L_in, const int& q_in, const double& beta_in, const int& sweeping_method_in) : 
	rng_seed(seed_in), L(L_in), q(q_in), beta(beta_in), sweeping_method(sweeping_method_in),
	uniform_random(uniform_real_distribution<double>(0,1)), 
	uniform_int_random(uniform_int_distribution<int>(1,q)){
	gen.seed(rng_seed);
	
	Energy = 0;
	
	if (sweeping_method == 1){
		Sweep = &Lattice::Typewriter;
	}
	
	for (int i=0; i<L; i++){
		lattice.push_back(vector<int>());
		for (int j=0; j<L; j++){
			lattice[i].push_back(uniform_int_random(gen));
		}
	}
	
	// Calculate initial energy
	int i_up, i_down, j_left, j_right;
	for (int i=0; i<L; i++){
		for (int j=0; j<L; j++){
			if (i == 0){i_up = L-1; i_down = i+1;}
			else if (i == L-1){i_up = i-1; i_down = 0;}
			else{i_up = i-1; i_down = i+1;}
			if (j == 0){j_left = L-1; j_right = j+1;}
			else if (j == L-1){j_left = j-1; j_right = 0;}
			else{j_left = j-1; j_right = j+1;}
			Energy += 0.5*(reverse_delta_function(lattice[i][j],lattice[i][j_left])
					+ reverse_delta_function(lattice[i][j],lattice[i][j_right])
					+ reverse_delta_function(lattice[i][j],lattice[i_up][j])
					+ reverse_delta_function(lattice[i][j],lattice[i_down][j]));
		}
	}
}

void Lattice::do_sweep(){
	(this->*Sweep)();
}

double Lattice::return_energy(){
	return Energy;
}

void Lattice::Typewriter(){
	int i_up, i_down, j_left, j_right;
	
	for (int i=0; i<L; i++){
		for (int j=0; j<L; j++){
			if (i == 0){i_up = L-1; i_down = i+1;}
			else if (i == L-1){i_up = i-1; i_down = 0;}
			else{i_up = i-1; i_down = i+1;}
			if (j == 0){j_left = L-1; j_right = j+1;}
			else if (j == L-1){j_left = j-1; j_right = 0;}
			else{j_left = j-1; j_right = j+1;}
			local_energy = reverse_delta_function(lattice[i][j],lattice[i][j_left])
						+ reverse_delta_function(lattice[i][j],lattice[i][j_right])
						+ reverse_delta_function(lattice[i][j],lattice[i_up][j])
						+ reverse_delta_function(lattice[i][j],lattice[i_down][j]);
			make_purposal(lattice[i][j]);
			Delta_Energy = reverse_delta_function(purposal,lattice[i][j_left])
						+ reverse_delta_function(purposal,lattice[i][j_right])
						+ reverse_delta_function(purposal,lattice[i_up][j])
						+ reverse_delta_function(purposal,lattice[i_down][j])
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

void Lattice::make_purposal(const int& lattice_spin){
	purposal = uniform_int_random(gen);
	while (lattice_spin == purposal){
		purposal = uniform_int_random(gen);
	}
}

void Lattice::check_purposal(const int& spin_i, const int& spin_j){
	p_accept = exp(-beta*(double)(Delta_Energy));
	if (p_accept >= 1.0){
		lattice[spin_i][spin_j] = purposal;
		Energy += Delta_Energy;
	}
	else if (p_accept > uniform_random(gen)){
		lattice[spin_i][spin_j] = purposal;
		Energy += Delta_Energy;
	}
}

void Lattice::print_conf(){
	for (int i=0; i<L; i++)
		cout << "--";
	cout << '\n';
	for (int i=0; i<L; i++){
		for (int j=0; j<L; j++){
			cout << lattice[i][j] << ' ';
		}
		cout << '\n';
	}
}

