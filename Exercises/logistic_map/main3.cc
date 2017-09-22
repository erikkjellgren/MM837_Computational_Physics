#include<iostream>
#include "newton_raphson_2d.h" 
#include "funcs.h" 

using namespace std;

template <class F> 
class G1 { 
	const F& f;

	public: 
		G1(const F& f_in) : f(f_in) {} 

		double operator() (const double& x, const double& r) const { 
			return x - f(x,r);
		}
};

template <class F> 
class G2 { 
	const F& f;
	const double eps=1e-6;

	public: 
		G2(const F& f_in) : f(f_in) {} 

		double operator() (const double& x, const double& r) const {
			return (f(x+0.5*eps,r) - f(x-0.5*eps,r))/(eps) + 1.0;
		}
};

template <class F> 
class Fn { 
	const F& f;
	int n; 

	public: 
		Fn(const F& f_in, int n_in) : f(f_in), n(n_in) {} 

		double operator() (const double& x, const double& r) const {
			double fn = f(x,r);  
			for (int i=1; i<n; i++) { 
				fn = f(fn,r);
			}	

			return fn;
		}
};

int main() { 
	const double tol=1e-10;
	const int nmax=1e4;
	double feigenbaum, x0, r0, k;
	vector<double> kvec;
	typedef LogisticMap mymap;

	mymap lm;
	
	x0 = 0.5;
	r0 = 3.5;
	k = 2;
	for (int i=0;i<3;i++){
		k = k*2;
		Fn<mymap> fn(lm,k); 
		G1<Fn<mymap> > g1(fn); 
		G2<Fn<mymap> > g2(fn);

		NewtonRaphson2D<G1<Fn<mymap> >, G2<Fn<mymap> > > nr(g1,g2);

		vector<double> ans = nr(x0, r0, tol, nmax);  
		kvec.push_back(ans[1]);
		x0 = ans[0];
		r0 = ans[1] + 0.001;
	}
	
	
	feigenbaum = (kvec[1]-kvec[0])/(kvec[2]-kvec[1]);

	cout << "rk-1= " << kvec[0] << '\n' << "rk= " << kvec[1] << '\n' << "rk+1= " << kvec[2] << '\n';
	cout << "Feigenbaum= "  << feigenbaum << endl;  

	
	return 0; 
}
