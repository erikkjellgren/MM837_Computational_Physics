/*****************************************************************************
 * Properties.cc
 * Contains methods to calculate properties of the system
 * ***************************************************************************/
 
#include"Properties.h"
#include<vector>

using namespace std;

properties::properties(vector<double>& energies_in) : 
			energies(energies_in){
				mean_energy = 0;
				for (int i=0; i<energies.size(); i++){
					mean_energy += (double)(energies[i]);
				}
				mean_energy = mean_energy/(double)(energies.size());
			}

			
void properties::calc_autocovariance(){
	double covariance, avg_energy_0, avg_energy_t;
	/*
	for (int h=0; h<energies.size(); h++){
		covariance = 0;
		for (int t=0; t<energies.size() - h; t++){
				covariance += (energies[t+h] - mean_energy)*(energies[t] - mean_energy);
		}
		autocovariance.push_back(covariance/(double)(energies.size() - h));
	}
	
	int n = energies.size();
	for (int t=0; t<n; t++){
		covariance = 0;
		avg_energy_0 = average_0(t,n);
		avg_energy_t = average_t(t, n);
		for (int tprime=0; t<n-t; tprime++){
				covariance += (energies[tprime] - avg_energy_0)*(energies[tprime+t] - avg_energy_t);
		}
		autocovariance.push_back(covariance/((double)(n-t)));
	}
	*/
	
}

double properties::average_0(const int& t, const int& n){
	double avg_energy_zero = 0;
	for (int tprime=0; tprime<n-t; tprime++){
		avg_energy_zero += energies[tprime];
	}
	return avg_energy_zero/((double)(n-t));
}

double properties::average_t(const int& t, const int& n){
	double avg_energy_zero = 0;
	for (int tprime=0; tprime<n-t; tprime++){
		avg_energy_zero += energies[tprime+t];
	}
	return avg_energy_zero/((double)(n-t));
}

void properties::calc_autocorrelation(){
	/*
	for (int i=0; i<autocovariance.size(); i++){
		autocorrelation.push_back(autocovariance[i]/autocovariance[0]);
	}
	*/
	int ndat = energies.size();
	int tmax = energies.size()/10;
	for (int t=0; t<tmax; t++){
		int n, t0;
		double xav0=0.0, xavt=0.0, r=0.0;
		n = ndat - t;
		for (t0=0; t0<n; t0++){
			xav0 += energies[t0];
			xavt += energies[t0+t];
		}
		xav0 /= n;
		xavt /= n;
		
		for (t0=0; t0<n; t0++){
			r += (energies[t0]-xav0)*(energies[t0+t]-xavt);
		}
		r /= n;
		autocorrelation.push_back(r);
		autocorrelation[t] /= autocorrelation[0];
		
	}
}

void properties::calc_integrated_autocorr(){
	/*
	double tau_int;
	for (int i=0; i<autocorrelation.size(); i++){
		tau_int = 0.5;
		for (int t=0; t<i; t++){
			tau_int += autocorrelation[t];
		}
		integrated_autocorr.push_back(tau_int);
	}
	*/
	int tau_int, tmax=energies.size()/10;
	for (int tcut=0; tcut<tmax; tcut++){
		tau_int = 0.0;
		for (int t=0; t<=tcut; t++){
			tau_int += autocorrelation[t];
		}
		integrated_autocorr.push_back(tau_int);
	}
}

vector<double> properties::return_integrated_autocorr(){
	return integrated_autocorr;
}

vector<double> properties::return_autocorr(){
	return autocorrelation;
}