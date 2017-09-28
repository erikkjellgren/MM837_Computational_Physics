/*****************************************************************************
 * examples.h 
 *
 * Some functors which can be used with the Integrator classes in integrators.h
 *****************************************************************************/

#ifndef __examples_h__
#define __examples_h__

#include<cmath>
#include<vector>

class SimpleHarmonicOscillator { 

	double m, k; 

	public: 
		SimpleHarmonicOscillator( const double& m_in, const double& k_in) : 
			m(m_in), k(k_in) {} 

		int getNDof() const { 
			return 1;
		}

		double operator() (int i, const std::vector<double>& q) const { 
			return -k*q[0]; 
		}

};
 
//----------------------------------------------------------------------------
template <class Ftype> 
class CentralForce {

	int n; 
	const Ftype& f;

	public: 
		CentralForce(int n_in, const Ftype& fin) : n(n_in), f(fin) {} 

		int getNDof() const {
			return 2*n;
		}

		double operator() (int i, const std::vector<double>& q) const {

			double ftot = 0.0;

			int p = (int) (i/2);

			for (int j = 0 ; j < n; j++) { 
				if (p ==j)
					continue;

				double xj=q[2*j]; double yj=q[2*j+1];
				double xp=q[2*p]; double yp=q[2*p+1];

				double r = sqrt(pow(xj-xp,2) + pow(yj-yp,2));
				
				if ((i%2)==0)
					ftot += f(r)*(xp-xj)/r;
				else
					ftot += f(r)*(yp-yj)/r;

			}
		}

};

//-------------------------------------------------------------------


#endif 
