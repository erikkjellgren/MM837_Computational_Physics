/*****************************************************************************
 * integrators.h
 *
 * Each integrator takes a template parameter, which is a functor that 
 * evaluates the forces. This template parameter also has a method 'getNDof()' 
 * which returns an integer corresponding to the number of degrees of freedom 
 * of the system. 
 *
 * ***************************************************************************/

#ifndef __integrators_h__ 
#define __integrators_h__

#include<stdexcept> 

template<class Forces, class Constraints> 
class NaiveEulerIntegrator { 

	double epsilon;
	const Forces& F;
	const Constraints& C; 

	std::vector<double> qt; 
	std::vector<double> pt; 

	public: 
		NaiveEulerIntegrator(const Forces& Fin, const Constraints& Cin, 
				const double& ein) : 
			F(Fin), C(Cin), epsilon(ein) {
			if (ein<0)
				throw(std::invalid_argument("epsilon must be positive"));
		}

		void setInitialConditions(const std::vector<double>& q0, 
				const std::vector<double>& p0) {
			int ndof = F.getNDof(); 
			if ((q0.size()!=ndof)||(p0.size()!=ndof))
				throw(std::logic_error("size of q0 and/or p0 not equal to ndof"));
			
			qt=q0; pt=p0;
			C(qt,pt);	
		}

		void operator() (std::vector<double>& qtp1, std::vector<double>& ptp1) { 
			int ndof = qt.size(); 		
			qtp1.resize(ndof); ptp1.resize(ndof); 

				for (int i=0; i<ndof; i++) {
					ptp1[i] = pt[i] + epsilon*F(i,qt);
					qtp1[i] = qt[i] + epsilon*pt[i];
				}

				C(qtp1,ptp1);
				qt=qtp1; pt=ptp1;
		}
};
//----------------------------------------------------------------------------

template<class Forces, class Constraints> 
class EulerCromerIntegrator { 

	double epsilon;
	const Forces& F; 
	const Constraints& C; 

	std::vector<double> qt; 
	std::vector<double> pt; 
	
	public: 
		EulerCromerIntegrator(const Forces& Fin, const Constraints& Cin, const double& ein) : 
			F(Fin), C(Cin), epsilon(ein) {
			if (ein<0) 
				throw(std::invalid_argument("epsilon must be positive"));
		}

		void setInitialConditions(const std::vector<double>& q0, 
				const std::vector<double>& p0) {
			int ndof = F.getNDof(); 
			if ((q0.size()!=ndof)||(p0.size()!=ndof))
				throw(std::logic_error("size of q0 and/or p0 not equal to ndof"));
			
			qt=q0; pt=p0;
			C(qt,pt);

		}

		void operator() (std::vector<double>& qtp1, std::vector<double>& ptp1) { 

			int ndof = qt.size(); 
			qtp1.resize(ndof); ptp1.resize(ndof); 

			for (int i=0; i<ndof; i++) {
				ptp1[i] = pt[i] + epsilon*F(i,qt);
				qtp1[i] = qt[i] + epsilon*ptp1[i];
			}

			C(qtp1,ptp1);
			qt=qtp1; pt=ptp1;

		}
};
//----------------------------------------------------------------------------

template<class Forces, class Constraints> 
class LeapfrogIntegrator { 

	double epsilon;
	const Forces& F; 
	const Constraints& C; 

	std::vector<double> qt; 
	std::vector<double> pt; 

	public: 
		LeapfrogIntegrator(const Forces& Fin, const Constraints& Cin, const double& ein) : 
			F(Fin), C(Cin), epsilon(ein) {
			if (ein<0) 
				throw(std::invalid_argument("epsilon must be positive"));
		}

		void setInitialConditions(const std::vector<double>& q0, 
				const std::vector<double>& p0) {
			int ndof = F.getNDof(); 
			if ((q0.size()!=ndof)||(p0.size()!=ndof))
				throw(std::logic_error("size of q0 and/or p0 not equal to ndof"));
		
			qt=q0; pt=p0;
			C(qt,pt); 	
		}

		void operator() (std::vector<double>& qtp1, std::vector<double>& ptp1) { 

			int ndof = F.getNDof(); 
			qtp1.resize(ndof); ptp1.resize(ndof); 

			for (int i=0; i<ndof; i++) {
				double ptp12 = pt[i] + 0.5*epsilon*F(i,qt); 	
				qtp1[i] = qt[i] + epsilon*ptp12;
				ptp1[i] = ptp12 + 0.5*epsilon*F(i,qtp1);
			}

			C(qtp1,ptp1); 	
			qt=qtp1; pt=ptp1;
		}
};

//----------------------------------------------------------------------------

template<class Forces, class Constraints> 
class RK2Integrator { 

	double epsilon;
	const Forces& F; 
	const Constraints& C; 

	std::vector<double> qt; 
	std::vector<double> pt; 

	public: 
		RK2Integrator(const Forces& Fin, const Constraints& Cin, const double& ein) : 
			F(Fin), C(Cin), epsilon(ein) {
			if (ein<0) 
				throw(std::invalid_argument("epsilon must be positive"));
		}

		void setInitialConditions(const std::vector<double>& q0, 
				const std::vector<double>& p0) {
			int ndof = F.getNDof(); 
			if ((q0.size()!=ndof)||(p0.size()!=ndof))
				throw(std::logic_error("size of q0 and/or p0 not equal to ndof"));
	
			qt=q0; pt=p0;
			C(qt,pt); 	
		}

		void operator() (std::vector<double>& qtp1, std::vector<double>& ptp1) { 

			int ndof = F.getNDof(); 
			qtp1.resize(ndof); ptp1.resize(ndof); 


			std::vector<double> temp(ndof); // qn + eps/2*k1 
			for (int i=0; i<ndof; i++) { 
				qtp1[i] = qt[i] + epsilon*(pt[i] + 0.5*epsilon*F(i,qt));
				temp[i] = qt[i] + 0.5*epsilon*pt[i];	
			}	

			for (int i=0; i<ndof; i++)  
						ptp1[i] = pt[i] + epsilon*F(i,temp);

			C(qtp1,ptp1); 	
			qt=qtp1; pt=ptp1;
		}
};

//-----------------------------------------------------------------------------
template<class Forces, class Constraints> 
class RK4Integrator { 

	double epsilon;
	const Forces& F; 
	const Constraints& C; 

	std::vector<double> qt; 
	std::vector<double> pt; 

	public: 
		RK4Integrator(const Forces& Fin, const Constraints& Cin, const double& ein) : 
			F(Fin), C(Cin), epsilon(ein) {
			if (ein<0) 
				throw(std::invalid_argument("epsilon must be positive"));
		}

		void setInitialConditions(const std::vector<double>& q0, 
				const std::vector<double>& p0) {
			int ndof = F.getNDof(); 
			if ((q0.size()!=ndof)||(p0.size()!=ndof))
				throw(std::logic_error("size of q0 and/or p0 not equal to ndof"));
		
			qt=q0; pt=p0;
			C(qt,pt);
		}

		void operator() (std::vector<double>& qtp1, std::vector<double>& ptp1) { 

			int ndof = F.getNDof(); 
			qtp1.resize(ndof); ptp1.resize(ndof); 

			const std::vector<double>& k1q=pt;
			std::vector<double> k2q(ndof),k3q(ndof),k4q(ndof); 
			std::vector<double> k1p(ndof),k2p(ndof),k3p(ndof),k4p(ndof),temp(ndof); 

			for (int i = 0 ; i<ndof ; i++) {	
				k1p[i] = F(i,qt);	
				k2q[i] = pt[i]+0.5*epsilon*k1p[i];
				temp[i] = qt[i] + 0.5*epsilon*k1q[i];
			}

			for (int i = 0 ; i<ndof ; i++) {
				k2p[i] = F(i, temp);
				k3q[i] = pt[i]+0.5*epsilon*k2p[i];
			}

			for (int i = 0 ; i<ndof ; i++) 
				temp[i] = qt[i] + 0.5*epsilon*k2q[i];	

			for (int i = 0 ; i<ndof ; i++) {
				k3p[i] = F(i,temp);
				k4q[i] = pt[i] + epsilon*k3p[i];
			}

			for (int i = 0 ; i<ndof ; i++) 
				temp[i] = qt[i] + epsilon*k3q[i];	

			for (int i = 0 ; i<ndof ; i++) 
				k4p[i] = F(i,temp);	


			for (int i=0; i<ndof; i++) { 
				ptp1[i] = pt[i] + epsilon/6.0*(k1p[i] + 2.0*k2p[i] + 2.0*k3p[i] + 
						k4p[i]);
				qtp1[i] = qt[i] + epsilon/6.0*(k1q[i] + 2.0*k2q[i] + 2.0*k3q[i] + 
						k4q[i]);

			}

			C(qtp1,ptp1);
			qt=qtp1; pt=ptp1;
		}
};


#endif 
