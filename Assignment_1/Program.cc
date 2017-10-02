
#include<iostream>
#include<cmath>
#include "integrators.h"
#include "forces.h"

using namespace std;

int main(){
	double mass=1.0, integration_step=0.1, delta=0.1, a=1.0, b=0.0, c=0.0;
	const double pi = 3.141592653589793238462643383279;
	int number_particles, steps=10;
	vector<double> position_x, velocity_x, acceleration_x;

	// Setup the system
	for (int i=0; i<number_particles; i++){
		position_x.push_back(0.0);
		velocity_x.push_back(sin(2.0*pi*((double)i+delta)/((double)number_particles)));
		acceleration_x.push_back(0.0);
	}
	
	integrators runIntegration(integration_step, number_particles);
	Forces runForces(a, b, c, number_particles, mass);
	
	for (int i=0; i<steps; i++){
		runForces.polynomicForce(position_x, acceleration_x);
		runIntegration.update_velocity(velocity_x, acceleration_x);
		runIntegration.update_position(position_x, velocity_x);
		runForces.polynomicForce(position_x, acceleration_x);
		runIntegration.update_velocity(velocity_x, acceleration_x);
	}
};