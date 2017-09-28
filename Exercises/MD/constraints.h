/****************************************************************************
 * constraints.h
 * Apply constraints to the motion.
 * **************************************************************************/

#ifndef __constraints_h__ 
#define __constraints_h__

#include <vector>

class NoConstraints { 

	public:
		void operator() (std::vector<double>& q, std::vector<double>& p) const {}

};

//----------------------------------------------------------------------------
//Assume the box is [-L,L] in each direction.
/*class SquareBox { 

	double Lmax; 
	double psize;
	int nd; 

	double dot(const std::vector<double>& v1, const std::vector<double>& v2) const
	{
		double res=0.0;
		for (int i=0; i<v1.size();i++)
			res+= v1[i]*v2[i];
		return res;
	}

	void check_collisions(std::vector<double>& qn, 
			std::vector<double>& pn) const {
		
		int npart = qn.size()/nd; 


		for (int i = 0 ; i<npart ;++i)  
			for (int j = 0 ; j<i ;++j) {

				std::vector<double> prel(nd), pcm(nd),rrel(nd); 
				for (int d=0; d<nd; ++d) { 
					rrel[d] = qn[i*nd+d]-qn[j*nd+d];
					prel[d] = pn[i*nd+d]-pn[j*nd+d];
				}

				double rrel_mag = dot(rrel,rrel);
				if (sqrt(rrel_mag) > 2.0*psize)
					continue;


				double prel_dot_rrel = dot(prel,rrel);
				
				for (int d=0; d<nd; ++d) {
					pcm[d]=0.5*(pn[i*nd+d]+pn[j*nd+d]);
					prel[d] = 2.0*rrel[d]*prel_dot_rrel/rrel_mag - prel[d];
					pn[i*nd+d] = pcm[d] + 0.5*prel[d]; 	
					pn[j*nd+d] = pcm[d] - 0.5*prel[d]; 	
					
				}

		}
	}

	public:

		SquareBox (const double& Lin, const double& psize_in, int nd_in) : 
			Lmax(Lin), psize(psize_in), nd(nd_in) {}

		void operator() (std::vector<double>& qn, std::vector<double>& pn) const {

			for (int i = 0 ; i < qn.size(); ++i) {
				if ((qn[i]+psize)>Lmax) {
					qn[i] = Lmax-psize;
					pn[i] *= -1.0;	
				}
				if ((qn[i]-psize)<(-Lmax)) {
					qn[i] = -Lmax+psize;
					pn[i] *= -1.0;	
				}
			}
	
			//check_collisions(qn,pn); 
		}
};

//---------------------------------------------------------------------------
//Periodic box
//

class PeriodicBox { 

	double Lmax; 
	int nd; 

	public:

		PeriodicBox (const double& Lin, int nd_in) : 
			Lmax(Lin), nd(nd_in) {}

		void operator() (std::vector<double>& qn, std::vector<double>& pn) const {

			for (int i = 0 ; i < qn.size(); ++i) {
				if (qn[i]>Lmax) {
					qn[i] -= 2*Lmax;
				}
				if (qn[i]<(-Lmax)) {
					qn[i] += 2*Lmax;
				}
			}
	
		}
};
*/
#endif 
