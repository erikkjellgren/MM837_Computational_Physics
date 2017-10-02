
#include<vector>

using namespace std;

class integrators{
	double integration_step, integration_step_half;
	int number_particles;
	public:
		integrators(const double& integration_step_, const int& number_particles_){
			integration_step = integration_step_;
			integration_step_half = integration_step/2.0;
			number_particles = number_particles_;
		}
		
		void update_position(vector<double>& position_x, const vector<double>& velocity_x){
			for (int i=0; i<number_particles-1; i++){
				position_x[i] += velocity_x[i]*integration_step;
			}
		}
		
		void update_velocity(vector<double>& velocity_x, const vector<double>& acceleration_x){
			for (int i=0; i<number_particles-1; i++){
				velocity_x[i] += acceleration_x[i]*integration_step_half;
			}
		}
};