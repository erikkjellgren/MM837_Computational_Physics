#include<iostream> 
#include<string> 
#include "cobweb.h" 
#include "funcs.h"

using namespace std; 

int main() { 

	double r; 
	cout << "Enter r: ";
	cin >> r;

	double x0; 
	cout << "Enter x0: ";
	cin >> x0; 
	
	int nmax; 
	cout << "Enter nmax: ";
	cin >> nmax; 
	
	string outfile; 
	cout << "Enter output file name: ";
	cin >> outfile; 

	LogisticMap f(r);
	CobWeb<LogisticMap> cweb(f, x0, nmax); 
	cweb(outfile); 

	return 0; 
}
