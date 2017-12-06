/*****************************************************************************
 * Lattice.cc
 * Container for operations done on the lattice
 * ***************************************************************************/

#include<vector>
#include<random>
#include<iostream>
#include<stack>
#include"Lattice.h"
 
using namespace std;

Lattice::Lattice(const int& seed_in, const int& L_in, const int& q_in, const double& beta_in, const int& sweeping_method_in, const int& hybrid_typewrite_freqency_in, const int& initial_lattice_in) : 
	rng_seed(seed_in), L(L_in), q(q_in), beta(beta_in), sweeping_method(sweeping_method_in), p_add_cluster(1.0 - exp(-1.0*beta_in)), 
	hybrid_typewrite_freqency(hybrid_typewrite_freqency_in), uniform_random(uniform_real_distribution<double>(0,1)), uniform_int_random(uniform_int_distribution<int>(1,q)),
	uniform_int_lattice(uniform_int_distribution<int>(0,L-1)), initial_lattice(initial_lattice_in), uniform_int_random_modified(uniform_int_distribution<int>(1,q-1)),
	p_accept_vector{exp(-beta*(double)(0)),exp(-beta*(double)(1)),exp(-beta*(double)(2)),exp(-beta*(double)(3)),exp(-beta*(double)(4))}{
	gen.seed(rng_seed);
	
	number_accepted = 0;
	number_purposes = 0;
	hybrid_counter = 0;
	
	if (sweeping_method == 1){Sweep = &Lattice::Typewriter;}
	else if (sweeping_method == 2){Sweep = &Lattice::wolff_cluster;}
	else if (sweeping_method == 3){Sweep = &Lattice::hybrid;}
	
	for (int i=0; i<L; i++){
		lattice.push_back(vector<int>());
		for (int j=0; j<L; j++){
			if (initial_lattice == 1){lattice[i].push_back(uniform_int_random(gen));}
			else {lattice[i].push_back(1);}
		}
	}
}

void Lattice::do_sweep(){
	(this->*Sweep)();
}

double Lattice::return_energy(){
		double Energy = 0.0;
		int i_up, i_down, j_left, j_right;
		for (int i=0; i<L; i++){
			for (int j=0; j<L; j++){
				if (i == 0){i_up = L-1; i_down = i+1;}
				else if (i == L-1){i_up = i-1; i_down = 0;}
				else{i_up = i-1; i_down = i+1;}
				if (j == 0){j_left = L-1; j_right = j+1;}
				else if (j == L-1){j_left = j-1; j_right = 0;}
				else{j_left = j-1; j_right = j+1;}
				Energy += reverse_delta_function(lattice[i][j],lattice[i][j_right])
						+ reverse_delta_function(lattice[i][j],lattice[i_down][j]);
			}
		}
	return Energy/(double)(2.0*L*L);
}

void Lattice::Typewriter(){
	int i_up, i_down, j_left, j_right, q_old, q_new, Delta_Energy;
	
	number_purposes += L*L;
	for (int i=0; i<L; i++){
		for (int j=0; j<L; j++){
			if (i == 0){i_up = L-1; i_down = i+1;}
			else if (i == L-1){i_up = i-1; i_down = 0;}
			else{i_up = i-1; i_down = i+1;}
			if (j == 0){j_left = L-1; j_right = j+1;}
			else if (j == L-1){j_left = j-1; j_right = 0;}
			else{j_left = j-1; j_right = j+1;}
			q_old = lattice[i][j];
			q_new = make_purposal(q_old);
			Delta_Energy = reverse_delta_function(q_new,lattice[i][j_left])
						+ reverse_delta_function(q_new,lattice[i][j_right])
						+ reverse_delta_function(q_new,lattice[i_up][j])
						+ reverse_delta_function(q_new,lattice[i_down][j])
						- reverse_delta_function(q_old,lattice[i][j_left])
						- reverse_delta_function(q_old,lattice[i][j_right])
						- reverse_delta_function(q_old,lattice[i_up][j])
						- reverse_delta_function(q_old,lattice[i_down][j]);
			check_purposal(i, j, q_new, Delta_Energy);
		}
	}
}

void Lattice::wolff_cluster(){
	int i_up, i_down, j_left, j_right, i_start, j_start, i, j, k_i, k_j;
	stack<pair<int,int>> cluster_buffer;
	pair<int,int> cur_site;
	
	i_start = uniform_int_lattice(gen);
	j_start = uniform_int_lattice(gen);
	
	const int q_old = lattice[i_start][j_start];
	const int q_new = make_purposal(q_old);
	
	number_purposes += L*L;
	number_accepted += 1;
	
	cluster_buffer.push(make_pair(i_start,j_start));
	lattice[i_start][j_start] = q_new;
	
	// Heavily based on cluster script from class
	while (!cluster_buffer.empty()) {
		vector<pair<int,int>> neighbors;
		cur_site = cluster_buffer.top();
		cluster_buffer.pop();

		i = cur_site.first; 
		j = cur_site.second;
		
		if (i == 0){i_up = L-1; i_down = i+1;}
		else if (i == L-1){i_up = i-1; i_down = 0;}
		else{i_up = i-1; i_down = i+1;}
		if (j == 0){j_left = L-1; j_right = j+1;}
		else if (j == L-1){j_left = j-1; j_right = 0;}
		else{j_left = j-1; j_right = j+1;}
		
		neighbors.push_back(make_pair(i_up,j));
		neighbors.push_back(make_pair(i_down,j));
		neighbors.push_back(make_pair(i,j_left));
		neighbors.push_back(make_pair(i,j_right));
		
		for (int k=0; k<neighbors.size(); k++){
			k_i = neighbors[k].first;
			k_j = neighbors[k].second;
			
			if (lattice[k_i][k_j] == q_old){
				if (uniform_random(gen) < p_add_cluster){
					lattice[k_i][k_j] = q_new;
					cluster_buffer.push(make_pair(k_i,k_j));
					number_accepted += 1;
				}
			}
		}
	}
}

void Lattice::hybrid(){
	hybrid_counter += 1;
	if (hybrid_counter%hybrid_typewrite_freqency == 0){Typewriter();}
	else {wolff_cluster();}
}

int Lattice::reverse_delta_function(const int& spin_i, const int& spin_j){
	int output;
	if (spin_i == spin_j){output = 0;}
	else {output = 1;}
	return output;
}

int Lattice::make_purposal(const int& lattice_spin){
	int purposal;
	purposal = uniform_int_random_modified(gen);
	if (lattice_spin == purposal){
		purposal = q;
	}
	return purposal;
}

void Lattice::check_purposal(const int& spin_i, const int& spin_j, const int& purposal, const int& Delta_Energy){
	if (Delta_Energy <= 0.0){
		lattice[spin_i][spin_j] = purposal;
		number_accepted += 1;
	}
	else if (p_accept_vector[Delta_Energy] > uniform_random(gen)){
		lattice[spin_i][spin_j] = purposal;
		number_accepted += 1;
	}
}

double Lattice::return_acceptance_ratio(){
	return (double)(number_accepted)/(double)(number_purposes);
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

double Lattice::return_magnetization(){
	double magnetization = 0.0;
	for (int i=0; i<L; i++){
		for (int j=0; j<L; j++){
			if (lattice[i][j] == 1){magnetization-=1.0;}
			else {magnetization+=1.0;}
		}
	}
	return magnetization/(double)(L*L);
}
