/*****************************************************************************
 * Properties.h
 * Headerfile for Properties.cc
 * ***************************************************************************/
 
#ifndef _PROPERTIES_H_
#define _PROPERTIES_H_

#include<vector>

using namespace std;

class properties{
	private:
		vector<int> energies;
		vector<double> autocorrelation, integrated_autocorr, autocovariance;
		double mean_energy;
	public:
		properties(vector<int>& energies_in);
		void calc_autocovariance();
		void calc_autocorrelation();
		void calc_integrated_autocorr();
		vector<double> return_integrated_autocorr();
};

#endif