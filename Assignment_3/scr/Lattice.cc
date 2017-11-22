/*****************************************************************************
 * Lattice.cc
 * Container for lattice information
 * ***************************************************************************/

#include <vector>
#include<random>
 
template<class Sweeper>
 class Lattice{
	const int seed, L, q;
	int Energy, Delta_Energy;
	const Sweeper& Sweep;
	public:
		Lattice(const Sweeper& Sweep_in, const int& seed_in, const int& L_in, const int& q_in) : 
			Sweep(Sweep_in), seed(seed_in), L(L_in), q(q_in){
				
			seed += 1;
			
			mt19937 gen(seed);
			uniform_int_distribution<double> uniform_int_random(1,q);
			
			// build lattice
			vector<vector<int>> lattice(L,vector<int>(L,0));
			for (int i=0; i<L; i++){
				for (int j=0; j<L; j++){
					lattice[i][j] = uniform_int_random(gen);
				}
			}
		}
			
		void do_sweep(){
			 Sweep(lattice, Delta_Energy);
			 Energy += Delta_Energy;
		}
		
		double return_energy(){
			return Energy;
		}
	 
 };