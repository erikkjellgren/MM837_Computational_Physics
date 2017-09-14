#include <vector>
#include <iostream>
#include <cmath>

class Quadratic{
	private:
		double a, b, c;
	public:
		void set_values (const double& x, const double& y, const double& z) {
		  a = x;
		  b = y;
		  c = z;
		}
		
		std::vector<double> QudraticRoots(){
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
};


int main(){
	std::vector<double>roots;
	Quadratic Quad;
	Quad.set_values(1, 1, -4);
	roots = Quad.QudraticRoots();
	std::cout << roots[0] << ' ' << roots[1] << '\n';
}