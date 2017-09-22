/*************************************************************************
 * cobweb.h 
 * make data for cobweb plots
 * *************************************************************************/

#ifndef __cobweb_h__
#define __cobweb_h__

#include<string> 
#include<fstream>
#include<iomanip>

template <class Func> 
class CobWeb {

	const Func& f;
	const double& x0; 
	int nmax; 

	public: 

		CobWeb(const Func& f_in, const double& x0_in, int nmax_in): f(f_in), 
			x0(x0_in), nmax(nmax_in) {} 

		void operator() (const std::string& outfile) const  { 
			
			std::ofstream fout(outfile.c_str()); 
			fout << std::setprecision(6);
			fout << x0 << "      " << 0.0 << std::endl;
	
			double xnp1, xn=x0;

			for (int i = 0 ; i < nmax ; i++) {
				xnp1 = f(xn); 
				fout << xn << "     " << xnp1 << std::endl; 
				fout << xnp1 << "     " << xnp1 << std::endl; 
				xn=xnp1;
			}

		}

}; 


#endif 
