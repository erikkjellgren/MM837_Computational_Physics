/****************************************************************************
 * program.cc
 * Heavily modified version of harmonic_oscillator.cc, from course MM837
 * **************************************************************************/

#include<iostream>
#include<fstream>
#include "potentials.h"
#include "integrators.h"
#include "wavefunction.h"
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

int main(int argc, char** argv) {
	int iteration, iterations_max, x_match, ode_steps_left, ode_steps_right, ode_steps, potential_type, NewtonRapshon;
	double check, check_old, x_min, x_max, tol, energy, delta_energy, k1, k2, x_match_parameter_1, x_match_parameter_2;
	double ode_step_size, q0_left, q0_right, p0_left, p0_right, qn_left, qn_right, pn_left, pn_right, delta_check;
	
	// Load parameters from file
	ifstream ifs("parameters.json");
	json j = json::parse(ifs);
	x_min = j["x_min"];
	x_max = j["x_max"];
	energy = j["energy_guess"];
	tol = j["energy_tolerance"];
	iterations_max = j["max_iterations"];
	ode_steps = j["ode_solver_steps"];
	k1 = j["potential_parameter_1"];
	k2 = j["potential_parameter_2"];
	potential_type = j["potential_type"];
	delta_energy = j["delta_energy"];
	x_match_parameter_1 = j["x_match_parameter_1"];
	x_match_parameter_2 = j["x_match_parameter_2"];
	NewtonRapshon = j["Enable_Newton_Raphson"];
	
	// Set integration/ode parameters
	if ((ode_steps%2)==0)
		ode_steps++;
	x_match = ode_steps/x_match_parameter_1+x_match_parameter_2;
	ode_step_size=(x_max-x_min)/double(ode_steps-1);
	ode_steps_left = x_match+1;
	ode_steps_right = ode_steps-x_match;
	
	// Set initial conditions
	q0_left=set_q0(potential_type, x_min);
	q0_right=set_q0(potential_type, x_max);
	p0_left=set_p0(potential_type, x_min);
	p0_right=set_p0(potential_type, x_max);
	qn_left=q0_left;
	pn_left=p0_left;
	qn_right=q0_right;
	pn_right=p0_right;

	// Make container for resulting wavefuntion
	vector<double> phi(ode_steps, 0.0); 
	vector<double> delta_phi(ode_steps, 0.0); 
	vector<double> x_value(ode_steps, 0.0);
	vector<double> potential_value(ode_steps, 0.0);

	string phi_file("phi.dat");
	ofstream fout(phi_file.c_str());


	cout << "energy = " << energy <<endl;

	
	for (int iteration=0 ; iteration< iterations_max; iteration++) { 
		
		Potentials potential(energy, k1, k2, potential_type); 
		RK4Integrator<Potentials> integrator_left(potential, ode_step_size);
		integrator_left.setInitialConditions(qn_left,pn_left); 
		RK4Integrator<Potentials> integrator_right(potential, -ode_step_size);
		integrator_right.setInitialConditions(qn_right,pn_right);

		phi[0] = q0_left;
		delta_phi[0] = p0_left;

		phi[ode_steps-1] = q0_right;
		delta_phi[ode_steps-1] = p0_right; 
		for (int n=1; n<ode_steps_left; n++) { 
			integrator_left(qn_left,pn_left,x_min+(n-1)*ode_step_size);
			
			phi[n] = qn_left;
			delta_phi[n] = pn_left;
			x_value[n] = x_min+(n-1)*ode_step_size;
			potential_value[n] = potential(qn_left, x_min+(n-1)*ode_step_size);
		}
		
		for (int n=1; n<ode_steps_right; n++) { 
			integrator_right(qn_right,pn_right,x_max-(n-1)*ode_step_size);
			
			phi[ode_steps-n-1] = qn_right;
			delta_phi[ode_steps-n-1] = pn_right;
			x_value[ode_steps-n-1] = x_max-(n-1)*ode_step_size;
			potential_value[ode_steps-n-1] = potential(qn_right, x_max-(n-1)*ode_step_size);
		}
		
		//Normalize the left integration results
		// such that x_match from left equals
		// x_match from right
		for (int n=0; n<ode_steps_left; n++) { 
			phi[n] *= qn_right/qn_left;
			delta_phi[n] *= qn_right/qn_left;
		}

		pn_left *= qn_right/qn_left; 
	
		check = (pn_right - pn_left)/(fabs(pn_right) + fabs(pn_left));
		
		cout <<setprecision(10)<< "energy = "<<energy <<", pn_right = " << pn_right << ", pn_left = "<< pn_left << ", f = "<< check<< ", de=" << delta_energy<<endl;

		if (fabs(check) < tol){break;}
		if (iteration==0){;}
		else if (NewtonRapshon==1){
			delta_check = (check - check_old)/delta_energy;
			if (fabs(delta_check) <= 1e-12){cout << "delta_check = 0, no NewtonRapshon step"<<'\n';}
			else{
			delta_energy = -check/delta_check;
			}
		}
		else if (fabs(check_old)<fabs(check)){delta_energy = -0.5*delta_energy;}

		energy += delta_energy; 
		check_old = check;
		qn_left=q0_left; pn_left=p0_left;
		qn_right=q0_right; pn_right=p0_right;

	}

	
	if (iteration==iterations_max)
		cout << "WARNING: max iterations reached" << endl;
	
	wavefunction psi_fun(phi, delta_phi, x_value, potential_value, ode_step_size);
	cout << psi_fun.position_expectation() << '\n';
	cout << psi_fun.position2_expectation() << '\n';
	cout << psi_fun.momentum_expectation() << '\n';
	cout << psi_fun.momentum2_expectation() << '\n';
	cout << psi_fun.potential_expectation() << '\n';
	cout << psi_fun.hamiltonian_expectation() << '\n';
	
	return 0;

}
