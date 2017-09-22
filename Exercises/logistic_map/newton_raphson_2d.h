/*******************************************************************************
 * newton_raphson_2d.h
 * newton rhapson method to solve the system of equations 
 *
 * g1(x*,y*) = 0 
 * g2(x*,y*) = 0 
 *
 * ***************************************************************************/

#ifndef __newton_raphson_h__ 
#define __newton_raphson_h__ 

#include<vector> 
#include<iostream>
#include<cmath>

template <class G1, class G2>
class NewtonRaphson2D {

	const G1& g1;
	const G2& g2; 

	const double eps=1e-6;

	double g11,g12,g21,g22,det;

	void compute_jacobian(const double& x, const double& y) {
		g11 = (g1(x+eps,y) - g1(x-eps,y))/(2.0*eps); 
		g12 = (g1(x,y+eps) - g1(x,y-eps))/(2.0*eps); 
		g21 = (g2(x+eps,y) - g2(x-eps,y))/(2.0*eps); 
		g22 = (g2(x,y+eps) - g2(x,y-eps))/(2.0*eps);

		det = g11*g22 - g12*g21; 
	}


	public: 
		NewtonRaphson2D(const G1& g1_in, const G2& g2_in): g1(g1_in), g2(g2_in) {}

		std::vector<double> operator() (const double& x_init, 
				const double& y_init, const double& tol, int nmax) {
	
			std::vector<double> ret; 
			double xn=x_init,yn=y_init;
			int n=0;

			while (true) { 
			
				std::cout << "iteration "<<n<<std::endl;

				compute_jacobian(xn,yn);
				double f1 = g1(xn,yn);
				double f2 = g2(xn,yn);

				std::cout << "f1 = " << f1 << std::endl;
				std::cout << "f2 = " << f2 << std::endl;
				std::cout << "det = " << det << std::endl;
				std::cout << "g11 = " << g11 << std::endl;
				std::cout << "g12 = " << g12 << std::endl;
				std::cout << "g21 = " << g21 << std::endl;
				std::cout << "g22 = " << g22 << std::endl;

				double delta1 = (g22*f1 - g12*f2)/det;
				double delta2 = (-g21*f1 + g11*f2)/det;
				
				std::cout << "delta1 = " << delta1 << std::endl;
				std::cout << "delta2 = " << delta2 << std::endl;

				double error = 0.5*sqrt(delta1*delta1 + delta2*delta2);
				if (error<tol)
					break;
				else if (n>=nmax) { 
					std::cout << "maximum iterations performed without convergence"
						<<std::endl;
					break;
				}
				
				xn -= delta1;
				yn -= delta2;
				std::cout << "xnp1 = " << xn << std::endl;
				std::cout << "ynp1 = " << yn << std::endl;

				n++;
			}
			ret.push_back(xn);
			ret.push_back(yn);

			return ret;
		}
	
};

#endif 
