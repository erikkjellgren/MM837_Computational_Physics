/*************************************************************************
 * bifurcation.h 
 * make data for bifurcation plots
 * *************************************************************************/

#ifndef __bifurcation_h__
#define __bifurcation_h__

#include<string> 
#include<fstream>
#include<iomanip>

template <class Func> 
class Bifurcation {

	const double& x0; 
	int nmax,nmin;

	public: 

		Bifurcation(const double& x0_in, int nmin_in, 
				int nmax_in): x0(x0_in), nmin(nmin_in), nmax(nmax_in) {} 

		void operator() (const double& rmin, const double& rmax, int nr,
				const std::string& outfile) const  { 
			
			std::ofstream fout(outfile.c_str()); 
			fout << std::setprecision(10); 

			double xnp1, xn,delta=(rmax-rmin)/(double)(nr);

			for (double r = rmin; r < rmax ; r+=delta) {  
 				Func f(r);
				xn=x0;	
				
				for (int i = 0 ; i < nmin ; i++) {
					xnp1 = f(xn); 
					xn=xnp1;
				}
				
				for (int i = nmin ; i < nmax ; i++) {
					xnp1 = f(xn); 
					fout << r << "     " << xnp1 << std::endl; 
					xn=xnp1;
				}
			}
		}
}; 


#endif 
