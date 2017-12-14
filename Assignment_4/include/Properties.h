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
	public:
		properties(const vector<double>& energies_in);
};

#endif