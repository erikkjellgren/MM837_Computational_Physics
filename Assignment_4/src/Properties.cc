/*****************************************************************************
 * Properties.cc
 * Contains methods to calculate properties of the system
 * ***************************************************************************/
 
#include"Properties.h"
#include<vector>

using namespace std;

properties::properties(const vector<double>& energies_in, const int& tmax_in) : 
			energies(energies_in), tmax(tmax_in){}

void properties::calc_autocorrelation(){
	// Heavily based on Physics/Scientific Computing by Konstantinos Anagnostopoulos
	const int ndat = energies.size();
	int n;
	double xav0, xavt;
	for(int t=0; t<tmax; t++){
		xav0 = 0.0;
		xavt = 0.0;
		autocorrelation.push_back(0.0);
		n = ndat - t;
		for(int t0=0; t0<n; t0++){
			xav0 += energies[t0];
			xavt += energies[t0+t];
		}
		xav0 /= n;
		xavt /= n;
		for(int t0=0; t0<n; t0++){
			autocorrelation[t] += (energies[t0]-xav0)*(energies[t0+t]-xavt);
		}
		autocorrelation[t] /= n;
	}
	const double norm = 1.0/autocorrelation[0];
	for (int i=0; i<autocorrelation.size(); i++){
		autocorrelation[i] *= norm;
	}
}

void properties::calc_integrated_autocorr(){
	// Heavily based on Physics/Scientific Computing by Konstantinos Anagnostopoulos
	for (int tcut=0; tcut<tmax; tcut++){
		integrated_autocorr.push_back(0.5);
		for (int t=0; t<=tcut; t++){
			integrated_autocorr[tcut] += autocorrelation[t];
		}
	}
}

vector<double> properties::return_integrated_autocorr(){
	return integrated_autocorr;
}

vector<double> properties::return_autocorr(){
	return autocorrelation;
}
