#include <iostream>
#include <cmath>

double factorial(int n){
	double fac = 1.0;
    
	for (int i=1; i<=n; i++){
		fac = fac*i;
	}
	return fac;
}

double sinus_thr(double x, double thr){
	double sinx=0.0, temp1=0.0, temp2=0.0, an=0.0, sum=0.0, check=1.0;
	int n=1;
	
	while (check > thr){
		temp1 = std::pow(-1.0, n-1)*std::pow(x, 2*n-1);
		temp2 = factorial(2*n-1);
		an = temp1/temp2;
		sinx = sinx + an;
		check = std::fabs(an/sinx);
		n = n + 1;
	}
	return sinx;
}

double sinus_thr_nofac(double x, double thr){
	double an=0.0, sum=0.0, check=1.0, anold, mx2, sinx;
	int n=2;
	
	anold = x;
	sinx  = x;
	mx2   = -1.0*std::pow(x, 2);
	while (check > thr){
		an = mx2/((2.0*n-1.0)*(2.0*n-2.0))*anold;
		sinx = sinx + an;
		check = std::fabs(an/sinx);
		n = n + 1;
		anold = an;
	}
	return sinx;
}

double sinus_thr_nofac_identity(double x, double thr){
	double an=0.0, sum=0.0, check=1.0, anold, mx2, sinx;
	int n=2, m;
	
	x = std::fmod(x,(2.0*M_PI));
	
	anold = x;
	sinx  = x;
	mx2   = -1.0*std::pow(x, 2);
	while (check > thr){
		an = mx2/((2.0*n-1.0)*(2.0*n-2.0))*anold;
		sinx = sinx + an;
		check = std::fabs(an/sinx);
		n = n + 1;
		anold = an;
	}
	return sinx;
}
