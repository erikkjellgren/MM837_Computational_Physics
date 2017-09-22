#include<iostream> 
#include<string> 
#include "bifurcation.h" 
#include "funcs.h"

using namespace std; 

int main() { 

	double rmin; 
	cout << "Enter rmin: ";
	cin >> rmin;
	
	double rmax; 
	cout << "Enter rmax: ";
	cin >> rmax;
	
	int nr; 
	cout << "Enter nr: ";
	cin >> nr;

	double x0; 
	cout << "Enter x0: ";
	cin >> x0; 
	
	int nmin; 
	cout << "Enter nmin: ";
	cin >> nmin; 
	
	int nmax; 
	cout << "Enter nmax: ";
	cin >> nmax; 
	
	string outfile; 
	cout << "Enter output file name: ";
	cin >> outfile; 

	Bifurcation<LogisticMap> bif(x0, nmin, nmax); 

	bif(rmin, rmax, nr, outfile); 

	return 0; 
}
