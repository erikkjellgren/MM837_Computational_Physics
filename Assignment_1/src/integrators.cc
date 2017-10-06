
#include<vector>
#include<iostream>

using namespace std;

void update_position(vector<double>& position_x, const vector<double>& velocity_x, const double& integration_step){
	const int number_particles = velocity_x.size();
	for (int i=0; i<number_particles; i++){
		position_x[i] += velocity_x[i]*integration_step;
	}
}

void update_velocity(vector<double>& velocity_x, const vector<double>& acceleration_x, const double& integration_step){
	const int number_particles = acceleration_x.size();
	const double integration_step_half = integration_step/2.0;
	for (int i=0; i<number_particles; i++){
		velocity_x[i] += acceleration_x[i]*integration_step_half;
	}
}
