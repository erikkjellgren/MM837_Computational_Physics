/*****************************************************************************
 * Properties.cc
 * Contains methods to calculate properties of the system
 * ***************************************************************************/
 
#include"Properties.h"
#include<vector>

using namespace std;

properties::properties(vector<int>& energies_in) : 
			energies(energies_in){
				mean_energy = 0;
				for (int i=0; i<energies.size(); i++){
					mean_energy += (double)(energies[i]);
				}
				mean_energy = mean_energy/(double)(energies.size());
			}
	
void properties::calc_autocovariance(){
	double covariance;
	
	for (int h=0; h<energies.size(); h++){
		covariance = 0;
		for (int t=0; t<energies.size() - h; t++){
				covariance += (energies[t+h] - mean_energy)*(energies[t] - mean_energy);
		}
		autocovariance.push_back(covariance/(double)(energies.size() - h));
	}
}

void properties::calc_autocorrelation(){
	for (int i=0; i<autocovariance.size(); i++){
		autocorrelation.push_back(autocovariance[i]/autocovariance[0]);
	}
}

void properties::calc_integrated_autocorr(){
	double tau_int;
	for (int i=0; i<autocorrelation.size(); i++){
		tau_int = 0.5;
		for (int t=0; t<i; t++){
			tau_int += autocorrelation[t];
		}
		integrated_autocorr.push_back(tau_int);
	}
}

vector<double> properties::return_integrated_autocorr(){
	return integrated_autocorr;
}