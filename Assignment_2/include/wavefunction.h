/*****************************************************************************
 * wavefunction.h
 *
 * Calculate the expectation values of the wavefunction
 * ***************************************************************************/

#include<vector>
using namespace std;

class wavefunction{
	
	vector<double> phi, phisq, delta_phi, delta2_phi, x_value, potential_value;
	double integration_step_size, norm;

	public:
		wavefunction(const vector<double>& phi_in, const vector<double>& delta_phi_in, const vector<double>& x_value_in, const vector<double>& potential_value_in, const double& integration_step_size_in):
			phi(phi_in), delta_phi(delta_phi_in), x_value(x_value_in), potential_value(potential_value_in), integration_step_size(integration_step_size_in) {
				
				for (int i=0; i<phi.size(); i++){
					phisq.push_back(phi[i]*phi[i]);
				}
				
				norm = simpsons_rule(phisq, integration_step_size);	
				for (int i=0; i<phi.size(); i++){
					phi[i] /= sqrt(norm);
					delta_phi[i] /= sqrt(norm);
				}
				
				for (int i=1; i<phi.size(); i++){
					delta2_phi.push_back((delta_phi[i]-delta_phi[i-1])/integration_step_size);
				}
				
			}
		double return_norm(){
			return norm;
		}
		vector<double> return_wavefunction(){
			return phi;
		}
		vector<double> return_delta_wavefunction(){
			return delta_phi;
		}
	
		double simpsons_rule(const vector<double>& phi, const double& integration_step_size) { 
			double output=0.0;
			
			output = phi[0]+phi[phi.size()-1];
			for (int i = 1 ; i<phi.size()-1; i++){
				if (i%2==0){output += 2.0*phi[i];}
				else {output += 4.0*phi[i];}
			}

			output *= integration_step_size/3.0;

			return output;
		}
		
		double position_expectation(){
			vector<double> phi_x_phi;
			double x_expectation;
			
			for (int i=0; i<phi.size(); i++){
				phi_x_phi.push_back(phi[i]*x_value[i]*phi[i]);
			}
			x_expectation = simpsons_rule(phi_x_phi, integration_step_size);
			return x_expectation;
		}
		
		double position2_expectation(){
			vector<double> phi_x2_phi;
			double x2_expectation;
			
			for (int i=0; i<phi.size(); i++){
				phi_x2_phi.push_back(phi[i]*x_value[i]*x_value[i]*phi[i]);
			}
			x2_expectation = simpsons_rule(phi_x2_phi, integration_step_size);
			return x2_expectation;
		}
		
		double momentum_expectation(){
			vector<double> phi_delta_phi_phi;
			double p_expectation;
			
			for (int i=0; i<phi.size(); i++){
				phi_delta_phi_phi.push_back(phi[i]*(-delta_phi[i]));
			}
			p_expectation = simpsons_rule(phi_delta_phi_phi, integration_step_size);
			return p_expectation;
		}
		
		double momentum2_expectation(){
			vector<double> phi_delta2_phi_phi;
			double p2_expectation;
			
			for (int i=0; i<delta2_phi.size(); i++){
				phi_delta2_phi_phi.push_back(phi[i]*(-delta2_phi[i]));
			}
			p2_expectation = simpsons_rule(phi_delta2_phi_phi, integration_step_size);
			return p2_expectation;
		}
		
		double potential_expectation(){
			vector<double> phi_v_phi;
			double v_expectation;
			
			for (int i=0; i<phi.size(); i++){
				phi_v_phi.push_back(phi[i]*potential_value[i]*phi[i]);
			}
			v_expectation = simpsons_rule(phi_v_phi, integration_step_size);
			return v_expectation;
		}
		
		double kinetic_expectation(){
			vector<double> phi_delta2_phi;
			double t_expectation;
			
			for (int i=0; i<phi.size(); i++){
				phi_delta2_phi.push_back(phi[i]*(-delta2_phi[i]));
			}
			t_expectation = simpsons_rule(phi_delta2_phi, integration_step_size);
			return t_expectation;
		}
	
		double hamiltonian_expectation(){
			vector<double> phi_h_phi;
			double h_expectation;
			
			for (int i=0; i<delta2_phi.size(); i++){
				phi_h_phi.push_back(phi[i]*potential_value[i]*phi[i]-phi[i]*delta2_phi[i]);
			}
			h_expectation = simpsons_rule(phi_h_phi, integration_step_size);
			return h_expectation;
		}
	
};
