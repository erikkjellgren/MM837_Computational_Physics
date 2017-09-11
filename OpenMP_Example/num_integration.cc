#include <iostream>
#include <omp.h>

double f(const double x){
	return x*x;
}


double trapezintegration(const double a, const double b, const double n){
	"a = start value of integration range";
	"b = end value of integration range";
	"n = number of integration slices";
	double integral=0.0, h=(b-a)/n;
	long loopbound = (long)n;
	"integral = the value of the integral";
	"h        = width of the numeric integration";
	integral = -(f(a)+f(b))/2.0;
	for (long i=1;i<=loopbound;i++){
		integral = integral + f(i*h);
	}
	integral = integral*(b-a)/n;
	return integral;
}


int main(){
	const double a=0.0, b=15.0, n=1e+10;
	double integral, integralMP;
	
	integral = trapezintegration(a, b, n);
	std::cout << integral << '\n';
}