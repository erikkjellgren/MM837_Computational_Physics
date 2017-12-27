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

Lattice::Lattice(const int& seed_in, const int& L_in, const double& beta_in, const int& sweeping_method_in, 
				 const int& typewriter_frequency_in, const double& proposal_delta_in) : 
	rng_seed(seed_in), 
	L(L_in),  
	beta(beta_in), 
	sweeping_method(sweeping_method_in), 
	p_add_cluster(1.0 - exp(-1.0*beta_in)), 
	typewriter_frequency(typewriter_frequency_in), 
	uniform_random(uniform_real_distribution<double>(0,1)), 
	uniform_angle_random(uniform_real_distribution<double>(-proposal_delta_in/2.0, proposal_delta_in/2.0)),
	uniform_int_lattice(uniform_int_distribution<int>(0,L_in-1)),
	uniform_real_x(uniform_real_distribution<double>(-1,1))
	{
		gen.seed(rng_seed);
		
		number_accepted = 0;
		number_purposes = 0;
		typewriter_counter = 0;
		
		if (sweeping_method == 1){Sweep = &Lattice::Typewriter;}
		else if (sweeping_method == 2){Sweep = &Lattice::wolff_cluster;}
		else if (sweeping_method == 3){Sweep = &Lattice::Microcanonical;}
		
		for (int i=0; i<L; i++){
			lattice.push_back(vector<double>());
			for (int j=0; j<L; j++){
				lattice[i].push_back(0.0);
			}
		}
		
		for (int i=0; i<L/2; i++){
			two_point_corr_vector.push_back(0.0);
		}
}


void Lattice::do_sweep(){
	(this->*Sweep)();
}


void Lattice::Typewriter(){
	int i_up, i_down, j_right, j_left;
	double Delta_Energy, proposal, p_accept;
	
	number_purposes += L*L;
	for (int j=0; j<L; j++){
		for (int i=0; i<L; i++){
			if (i == 0){i_up = L-1; i_down = i+1;}
			else if (i == L-1){i_up = i-1; i_down = 0;}
			else{i_up = i-1; i_down = i+1;}
			if (j == 0){j_left = L-1; j_right = j+1;}
			else if (j == L-1){j_left = j-1; j_right = 0;}
			else{j_left = j-1; j_right = j+1;}
			
			proposal = lattice[i][j] + uniform_angle_random(gen);
			if (proposal<-M_PI){proposal += 2.0*M_PI;}
			else if(proposal>(M_PI)){proposal -= 2.0*M_PI;}
			
			Delta_Energy 	= -cos(proposal - lattice[i][j_right])
							- cos(proposal - lattice[i][j_left])
							- cos(proposal - lattice[i_up][j])
							- cos(proposal - lattice[i_down][j])
							+ cos(lattice[i][j] - lattice[i][j_right])
							+ cos(lattice[i][j] - lattice[i][j_left])
							+ cos(lattice[i][j] - lattice[i_up][j])
							+ cos(lattice[i][j] - lattice[i_down][j]);
			
			p_accept = exp(-beta*Delta_Energy);
			if (uniform_random(gen) < p_accept){
				lattice[i][j] = proposal;
				number_accepted += 1;
			}
		}
	}
}


void Lattice::Microcanonical(){
	typewriter_counter += 1;
	if (typewriter_counter%(typewriter_frequency+1) == 0){Typewriter();}
	else {
		for (int i=0; i<L; i++){
			for (int j=0; j<L; j++){
				overrelaxation(i, j);
			}
		}
	}
}


void Lattice::overrelaxation(const int& spin_i, const int& spin_j){
	int i_up, i_down, j_right, j_left;
	double sigma_prime_x, sigma_prime_y, sigma_prime;
	double V_x = 0.0;
	double V_y = 0.0;
	double sigma_x = 0.0;
	double sigma_y = 0.0;
	
	if (spin_i == 0){i_up = L-1; i_down = spin_i+1;}
	else if (spin_i == L-1){i_up = spin_i-1; i_down = 0;}
	else{i_up = spin_i-1; i_down = spin_i+1;}
	if (spin_j == 0){j_left = L-1; j_right = spin_j+1;}
	else if (spin_j == L-1){j_left = spin_j-1; j_right = 0;}
	else{j_left = spin_j-1; j_right = spin_j+1;}
	
	V_x += cos(lattice[spin_i][j_left]);
	V_x += cos(lattice[spin_i][j_right]);
	V_x += cos(lattice[i_up][spin_j]);
	V_x += cos(lattice[i_down][spin_j]);
	
	V_y += sin(lattice[spin_i][j_left]);
	V_y += sin(lattice[spin_i][j_right]);
	V_y += sin(lattice[i_up][spin_j]);
	V_y += sin(lattice[i_down][spin_j]);
	
	sigma_prime = 2.0*(cos(lattice[spin_i][spin_j])*V_x + sin(lattice[spin_i][spin_j])*V_y)/(V_x*V_x + V_y*V_y);
	sigma_prime_x = sigma_prime*V_x - cos(lattice[spin_i][spin_j]);
	sigma_prime_y = sigma_prime*V_y - sin(lattice[spin_i][spin_j]);
	
	lattice[spin_i][spin_j] = atan2(sigma_prime_y, sigma_prime_x);
}


void Lattice::wolff_cluster(){
	int i_up, i_down, j_left, j_right, i_start, j_start, i, j, k_i, k_j;
	double sigma_x1, sigma_x2, sigma_y1, sigma_y2, r_x, r_y, s1, s2, sigma_prime_x, sigma_prime_y, size;
	stack<pair<int,int>> cluster_buffer;
	pair<int,int> cur_site;
	
	// Making lattice to check that a site is
	// only flipped once during a sweep
	vector<vector<int>> lattice_check;
	for (int i=0; i<L; i++){
		lattice_check.push_back(vector<int>());
		for (int j=0; j<L; j++){
			lattice_check[i].push_back(0);
		}
	}
	
	i_start = uniform_int_lattice(gen);
	j_start = uniform_int_lattice(gen);
	
	r_x = uniform_real_x(gen);
	r_y = uniform_real_x(gen);
	size = sqrt(r_x*r_x+r_y*r_y);
	r_x /= size;
	r_y /= size;
	
	number_purposes += L*L;
	number_accepted += 1;
	
	cluster_buffer.push(make_pair(i_start,j_start));
	
	sigma_x1 = cos(lattice[i_start][j_start]);
	sigma_y1 = sin(lattice[i_start][j_start]);
	s1 = sigma_x1*r_x + sigma_y1*r_y;
	lattice_check[i_start][j_start] = 1;

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
		
		if(lattice_check[i_up][j] == 0){neighbors.push_back(make_pair(i_up,j));}
		if(lattice_check[i_down][j] == 0){neighbors.push_back(make_pair(i_down,j));}
		if(lattice_check[i][j_left] == 0){neighbors.push_back(make_pair(i,j_left));}
		if(lattice_check[i][j_right] == 0){neighbors.push_back(make_pair(i,j_right));}
		
		sigma_x1 = cos(lattice[i][j]);
		sigma_y1 = sin(lattice[i][j]);
		s1 = sigma_x1*r_x + sigma_y1*r_y;
		
		for (int k=0; k<neighbors.size(); k++){
			k_i = neighbors[k].first;
			k_j = neighbors[k].second;
			
			sigma_x2 = cos(lattice[k_i][k_j]);
			sigma_y2 = sin(lattice[k_i][k_j]);
			s2 = sigma_x2*r_x + sigma_y2*r_y;
			
			if (-2.0*beta*s1*s2 > 0){;}
			if (uniform_random(gen) < 1 - exp(-2.0*beta*s1*s2)){
				lattice_check[k_i][k_j] = 1;
				cluster_buffer.push(make_pair(k_i,k_j));
				number_accepted += 1;
			}
		}
	}
	
	// change all the spins
	for (int i=0; i<L; i++){
		for (int j=0; j<L; j++){
			if (lattice_check[i][j] == 1){
				sigma_x1 = cos(lattice[i][j]);
				sigma_y1 = sin(lattice[i][j]);
				s1 = sigma_x1*r_x + sigma_y1*r_y;
				sigma_prime_x = sigma_x1 - 2.0*s1*r_x;
				sigma_prime_y = sigma_y1 - 2.0*s1*r_y;
				lattice[i][j] = atan2(sigma_prime_y, sigma_prime_x);
			}
		}
	}
}

double Lattice::return_energy(){
		double Energy = 0.0;
		int i_down, j_right;
		for (int i=0; i<L; i++){
			for (int j=0; j<L; j++){
				if (i == 0){i_down = i+1;}
				else if (i == L-1){i_down = 0;}
				else{i_down = i+1;}
				if (j == 0){j_right = j+1;}
				else if (j == L-1){j_right = 0;}
				else{j_right = j+1;}
				Energy += -cos(lattice[i][j] - lattice[i][j_right])
						- cos(lattice[i][j] - lattice[i_down][j]);
			}
		}
	return Energy/(double)(2.0*L*L);
}


double Lattice::return_acceptance_ratio(){
	return (double)(number_accepted)/(double)(number_purposes);
}


vector<vector<double>> Lattice::return_lattice(){
	return lattice;
}


void Lattice::two_point_corr(){
	int j_new, i_new;
	int counter = 0;
	double e;
	double e_x=0.0;
	double e_y=0.0;

	vector<double> two_point_corr_vector_temp;
	for (int i=0; i<L/2; i++){
		two_point_corr_vector_temp.push_back(0.0);
	}
	
	for (int i=0; i<L; i++){
		for (int j=0; j<L; j++){
			e_x += cos(lattice[i][j]);
			e_y += sin(lattice[i][j]);
		}
	}
	
	e_x /= (double)(L*L);
	e_y /= (double)(L*L);
	e = e_x*e_x + e_y*e_y;
	
	for (int i=0; i<L; i++){
		for (int j=0; j<L; j++){
			counter += 2;
			e_x = cos(lattice[i][j]);
			e_y = sin(lattice[i][j]);
			for (int k=1; k<L/2; k++){
				if (i+k > L-1){i_new = i+k - L;}
				else {i_new = i+k;}
				two_point_corr_vector_temp[k] += e_x*cos(lattice[i_new][j]) + e_y*sin(lattice[i_new][j]);
			}
			for (int k=1; k<L/2; k++){
				if (j+k > L-1){j_new = j+k - L;}
				else {j_new = j+k;}
				two_point_corr_vector_temp[k] += e_x*cos(lattice[i][j_new]) + e_y*sin(lattice[i][j_new]);
			}
		}
	}
	
	for (int i=0; i<L/2; i++){
		two_point_corr_vector[i] += two_point_corr_vector_temp[i]/(double)(counter) - e;
	}
}

vector<double> Lattice::return_two_point_corr(){
	vector<double> two_point_corr_vector_temp;
	double norm;
	norm = two_point_corr_vector[1];
	for (int i=1; i<L/2; i++){
		two_point_corr_vector_temp.push_back(two_point_corr_vector[i]/norm);
	}
	return two_point_corr_vector_temp;
}