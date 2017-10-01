
#include<vector>
#include<cmath>
#include "forces.h"
#include "integrators.h"

class propagate{
	double mass, integration_step, delta;
	const double pi = 3.141592653589793238462643383279;
	int N;
	vector<double> position_x, velocity_x, acceleration_x;
	vector<vector<double>> interactionlist;
	public:
		void initialize(const double& mass_, const double& integration_step_, const double& delta_, const int& N_){
			mass = mass_;
			integration_step =integration_step_;
			delta = delta_;
			N = N_;
			// Setup the system
			for (int i=0; i<N; i++){
				position_x.push_back(0.0);
				velocity_x.push_back(sin(2.0*pi*((double)i+delta)/((double)N)));
				acceleration_x.push_back(0.0);
			}
			
			// make the interaction list;
			// first create the array
			for (int i=0; i<N; i++){
				interactionlist.push_back(vector<double>)
				for (int j=0; j<2; j++){
					interactionlist[i].push_back(0.0);
				}
			}
			// then fill it up
			for (int i=0; i<N; i++){
				if (i+1 == N){
					interactionlist[i][0] = i;
					interactionlist[i][1] = 0;
				}
				else{
					interactionlist[i][0] = i;
					interactionlist[i][1] = i+1;
				}
			}
		}
};