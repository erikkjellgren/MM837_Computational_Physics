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
		vector<double> autocorrelation, integrated_autocorr, autocovariance, energies;
		double mean_energy;
	public:
		properties(vector<double>& energies_in);
		void calc_autocovariance();
		void calc_autocorrelation();
		void calc_integrated_autocorr();
		vector<double> return_integrated_autocorr();
		vector<double> return_autocorr();
		double average_0(const int& t, const int& n);
		double average_t(const int& t, const int& n);
};

#endif