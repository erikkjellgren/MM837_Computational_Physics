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
		const vector<double> energies;
		vector<double> autocorrelation, integrated_autocorr;
		const int tmax;
	public:
		properties(const vector<double>& energies_in, const int& tmax_in);
		void calc_autocorrelation();
		void calc_integrated_autocorr();
		vector<double> return_integrated_autocorr();
		vector<double> return_autocorr();
};

#endif