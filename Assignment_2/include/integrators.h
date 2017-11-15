/*****************************************************************************
 * integrators.h
 *
 * Hevily modified version of integrators.h, from course MM837
 * ***************************************************************************/

template<class Forces> 
class RK4Integrator { 
	double epsilon, qt, pt;
	const Forces& F; 

	public: 
		RK4Integrator(const Forces& Fin, const double& ein) : 
			F(Fin), epsilon(ein) {}

		void setInitialConditions(const double& q0, const double& p0) {
			qt=q0; pt=p0;
		}

		void operator() (double& qtp1, double& ptp1, const double& x) { 
			double k1q,k2q,k3q,k4q,k1p,k2p,k3p,k4p; 

			k1q = pt;
			k1p = F(qt,x);	
			k2q = pt + 0.5*epsilon*k1p;
			k2p = F(qt + 0.5*epsilon*k1q,x);
			k3q = pt + 0.5*epsilon*k2p;
			k3p = F(qt + 0.5*epsilon*k2q,x);
			k4q = pt + epsilon*k3p;
			k4p = F(qt + epsilon*k3q,x);	

			ptp1 = pt + epsilon/6.0*(k1p + 2.0*k2p + 2.0*k3p + k4p);
			qtp1 = qt + epsilon/6.0*(k1q + 2.0*k2q + 2.0*k3q + k4q);

			qt=qtp1; pt=ptp1;
		}
};