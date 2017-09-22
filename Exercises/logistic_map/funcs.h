/****************************************************************************
 * funcs.h 
 * function objects to be used in an analysis of bifurcation points. 
 * ************************************************************************/

#ifndef __funcs_h__
#define __funcs_h__

#include <cmath>
using namespace std; 

class LogisticMap { 
	private:
		const double& r;

	public: 
		LogisticMap(const double& r_in) : r(r_in) {}
		LogisticMap() : r(0.0) {}

	  double operator() (const double& x) const { 
			return r*x*(1.0-x);
		}
	  
		double operator() (const double& x, const double& rin) const { 
			return rin*x*(1.0-x);
		}
};

class Ecology {
	private:
		const double& r;

	public: 
		Ecology(const double& r_in) : r(r_in) {}
		Ecology() : r(0.0) {}

	  double operator() (const double& x) const { 
			return x*exp(r*(1.0-x));
		}
	  
		double operator() (const double& x, const double& rin) const { 
			return x*exp(rin*(1.0-x));
		}
};


class Mouse {
	private:
		const double& r;
		const double& b=-1.0;

	public: 
		Mouse(const double& r_in) : r(r_in) {}
		Mouse() : r(0.0) {}

	  double operator() (const double& x) const { 
			return exp(b*x*x)+r;
		}
	  
		double operator() (const double& x, const double& rin) const { 
			return exp(b*x*x)+rin;
		}
};

class Tent {
	private:
		const double& r;

	public: 
		Tent(const double& r_in) : r(r_in) {}
		Tent() : r(0.0) {}

	  double operator() (const double& x) const { 
			return r*(1.0-2.0*fabs(x-0.5));
		}
	  
		double operator() (const double& x, const double& rin) const { 
			return rin*(1.0-2.0*fabs(x-0.5));
		}
};

class Quartic {
	private:
		const double& r;

	public: 
		Quartic(const double& r_in) : r(r_in) {}
		Quartic() : r(0.0) {}

	  double operator() (const double& x) const { 
			return r*(1.0-(2.0*x-1.0)*(2.0*x-1.0)*(2.0*x-1.0)*(2.0*x-1.0));
		}
	  
		double operator() (const double& x, const double& rin) const { 
			return rin*(1.0-(2.0*x-1.0)*(2.0*x-1.0)*(2.0*x-1.0)*(2.0*x-1.0));
		}
};

#endif 
