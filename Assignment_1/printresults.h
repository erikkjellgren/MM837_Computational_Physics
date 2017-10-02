
#include<vector>

using namespace std;

class print_results{
	int number_particles;
	FILE * energyfile;
	public:
		print_results(const int& number_particles_){
			number_particles = number_particles_;
			energyfile = fopen("energy.txt", "w");
		}
		
		vector<double> getEnergy(const vector<double>& position_x, const vector<double>& velocity_x){
			vector<double> energy_vector;
			double kintetic_energy = 0.0;
			double potential_energy = 0.0;
			for (int i=0; i<number_particles-1; i++){
				kintetic_energy += velocity_x[i]*velocity_x[i];
				if (a != 0.0){potential_energy += 0.5*a*(position_x[i] - position_x[i+1])*(position_x[i] - position_x[i+1]);}
				if (b != 0.0){potential_energy += 1.0/3.0*b*(position_x[i] - position_x[i+1])*(position_x[i] - position_x[i+1])*(position_x[i] - position_x[i+1]);}
				if (c != 0.0){potential_energy += 0.25*c*(position_x[i] - position_x[i+1])*(position_x[i] - position_x[i+1])*(position_x[i] - position_x[i+1])*(position_x[i] - position_x[i+1]);}
			}
			kintetic_energy *= 0.5*mass;
			energy_vector.push_back(kintetic_energy);
			energy_vector.push_back(potential_energy);
			return energy_vector;
		}
		
		void writeEnergy(const double& kinetic_energy, const double& potential_energy){
			fprintf(energyfile, "%f", kintetic_energy);
			fprintf(energyfile, " ");
			fprintf(energyfile, "%f", potential_energy);
			fprintf(energyfile, "\n");	
		};
		
		void close_output_files(){
			fclose(energyfile);
		}
};
