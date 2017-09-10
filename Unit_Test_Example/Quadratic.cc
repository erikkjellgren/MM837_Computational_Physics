#include <vector>
#include <iostream>
#include <cmath>

std::vector<double> quadraticroot(double a, double b, double c){
	double x1, x2, determinant;
	std::vector<double> roots;
	
	determinant = b*b-4.0*a*c;
	if (determinant > 0){
		x1 = (-b + std::sqrt(determinant))/(2.0*a);
		x2 = (-b - std::sqrt(determinant))/(2.0*a);
	}
	else if (determinant == 0){
		x1 = -b/(2.0*a);
		x2 = -b/(2.0*a);
	}
	else{
		x1 = 404;
		x2 = 404;
	}
	roots.push_back(x1);
	roots.push_back(x2);
	return roots;
}
