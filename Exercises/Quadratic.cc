#include <iostream>
#include <cmath>

int main(){
	double a, b, c, determinant, x1, x2;
	std::cout << "Enter a: ";
	std::cin >> a;
	std::cout << "Enter b: ";
	std::cin >> b;
	std::cout << "Enter c: ";
	std::cin >> c;
	
	determinant = b*b-4.0*a*c;
	if (determinant > 0){
		x1 = (-b + std::sqrt(determinant))/(2.0*a);
		x2 = (-b - std::sqrt(determinant))/(2.0*a);
	
		std::cout << "x1=" << x1 << "\n";
		std::cout << "x2=" << x2 << "\n";
	}
	else if (determinant == 0){
		x1 = -b/(2.0*a);
		
		std::cout << "x1=x2=" << x1 << "\n";
	}
	else{
		std::cout << "Complex solutions not supported \n";
	}
		
}