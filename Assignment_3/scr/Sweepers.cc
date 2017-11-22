/****************************************************************************
 * Sweepers.cc
 * Containts the code for different sweeping methods
 * **************************************************************************/

#include <vector>
#include <random>
 
class Typewriter{
	int seed, L, q;
	public:
		Typewriter(const int& seed_in, const int& L_in, const int& q_in) : 
			seed(seed_in), L(L_in), q(q_in){
				
			mt19937 gen(seed);
			uniform_real_distribution<double> uniform_random(0,1);
			uniform_int_distribution<double> uniform_int_random(1,q);
		}
		
		void operator() (vector<vector<int>>& lattice){
			
			// Do corners
			lattice[0][0];
			lattice[0][L-1];
			lattice[L-1][0];
			lattice[L-1][L-1];
			
			// Do top
			for (int j=1; j<L-1; j++){
				lattice[0][j];
			}
			// Do bottom
			for (int j=1; j<L-1; j++){
				lattice[L-1][j];
			}
			// Do left
			for (int i=1; i<L-1; i++){
				lattice[i][0];
			}			
			// Do right
			for (int i=1; i<L-1; i++){
				lattice[i][L-1];
			}	
			
			// Do middle
			for (int i=1; i<L-1; i++){
				for (int j=1; j<L-1; j++){
					lattice[i][j];
				}
			}
		}
};
 

class WolffCluster{
	
	public:
		void operator() (){
			
		}
};
 
 
class TypewriterClusterHybrid{
	
	public:
		void operator() (){
			
		}
};