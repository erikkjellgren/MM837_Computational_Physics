/*****************************************************************************
 * examples.h 
 *
 * Some functors which can be used with the Integrator classes in integrators.h
 *****************************************************************************/

#ifndef __examples_h__
#define __examples_h__

#include<cmath>
#include<vector>

class SimplePendulum { 

	double m, L; 
	const double g=9.8;

	public: 
		SimplePendulum( const double& m_in, const double& L_in) : 
			m(m_in), L(L_in) {} 

		int getNDof() const { 
			return 1;
		}

		double operator() (int i, const std::vector<double>& q) const { 
			return L*m*g*sin(q[0]); 
		}

};

//----------------------------------------------------------------------------
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
template <class ForceLaw> 
class CentralForce {

	const ForceLaw& f;
	int N;

	public: 

	CentralForce (const ForceLaw& fin, int Nin) : 
		f(fin), N(Nin) {}

	int getNDof() const { 
		return 2*N; 
	}


	double operator() (int i, const std::vector<double>& q) const {

		int ix=i; 
		int iy=i+1; 

		if ((i%2)!=0) {
			ix=i-1; iy=i;
		}
		
		double ftot=0.0;
		for (int n = 0 ; n<N ; n++) {

			if ((ix/2)==n)
				continue;

			double r = sqrt(pow(q[ix]-q[2*n],2) + pow(q[iy]-q[2*n+1],2));

			if (ix==i)
				ftot += (q[i]-q[2*n])*f(r)/r;
			else 
				ftot += (q[i]-q[2*n+1])*f(r)/r;
		}
		return ftot; 
	}

	double calcPot (const std::vector<double>& q) {

		double Etot=0.0;
		for (int i = 0; i < (q.size()/2) ;i++) {
			for (int j = 0 ; j<i; j++) {
				double r = sqrt(pow(q[2*i]-q[2*j],2) + pow(q[2*i+1]-q[2*i+1],2));
				Etot += f.pot(r);
			}
		}
		return Etot; 
	}
};
//----------------------------------------------------------------------------
template <class ForceLaw> 
class CentralForce2 {

	const ForceLaw& f;
	int N;

	public: 

	CentralForce2 (const ForceLaw& fin, int Nin) : 
		f(fin), N(Nin) {}

	int getNDof() const { 
		return 2*N; 
	}


	double operator() (int i, const std::vector<double>& q) const {

		int ix=i; 
		int iy=i+1; 

		if ((i%2)!=0) {
			ix=i-1; iy=i;
		}
		
		double r = sqrt(pow(q[ix],2) + pow(q[iy],2));
		double ftot = q[i]*f(r)/r;
		
		return ftot; 
	}

	double calcPot (const std::vector<double>& q) {

		double Etot=0.0;
		for (int i = 0; i < (q.size()/2) ;i++) {
			double r = sqrt(pow(q[2*i],2) + pow(q[2*i+1],2));
			Etot += f.pot(r);
		}
		return Etot; 
	}
};

//-----------------------------------------------------------------
class UniformForceField { 

	double k;
	int d;
	int nd;
	int npart;

	public:

	UniformForceField(const double& kin, int din, int ndin, int npart_in) : 
		k(kin), d(din), nd(ndin), npart(npart_in) {}

	int getNDof() const { return nd*npart;}

	double operator() (int i, const std::vector<double>& q) const {

		if (i%nd==d)
			return k; 
		else 
			return 0;
	}

	double calcPot (const std::vector<double>& q) {

		double Etot=0.0;
		for (int i = 0; i < (q.size()/2) ;i++) {
			Etot += -k*q[2*i];
		}
		return Etot; 
	}

};

//-----------------------------------------------------------------
template<class Force1, class Force2> 
class TwoForces { 

	Force1 f1; 
	Force2 f2; 

	public:

	TwoForces(const Force1& f1in, const Force2& f2in) : 
		f1(f1in), f2(f2in) {}

	int getNDof() const { return f1.getNDof();}

	double operator() (int i, const std::vector<double>& q) const {
			return f1(i,q)+f2(i,q);
	}

	double calcPot(const std::vector<double>& q) {
		return f1.calcPot(q)+f2.calcPot(q); 	
	}

};


//-------------------------------------------------------------------
class InverseSquareForce { 

	double k; 

	public:

	InverseSquareForce(const double& kin): k(kin) {}

	double operator() (const double& r) const {return k/(r*r);}
	
	double pot(const double& r) const {return k/r;}
};

class HarmonicOscillatorForce { 

	double k; 

	public:

	HarmonicOscillatorForce(const double& kin): k(kin) {}

	double operator() (const double& r) const {return -k*r;}
	
	double pot(const double& r) const {return 0.5*k*r*r;}
};

class NoForce { 

	public:

	double operator() (const double& r) const {return 0.0;}
	double pot(const double& r) const {return 0.0;}
};


#endif 
