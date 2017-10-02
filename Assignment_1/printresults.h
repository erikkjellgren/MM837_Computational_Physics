
#include<vector>

using namespace std;

class print_results{
	FILE * energyfile, velocityfile;
	public:
		print_results(){
			energyfile = fopen("energy.txt", "w");
			velocityfile = fopen("velocities.txt","w")
		}
		
		void writeEnergy(const double& kinetic_energy, const double& potential_energy){
			fprintf(energyfile, "%f", kintetic_energy);
			fprintf(energyfile, " ");
			fprintf(energyfile, "%f", potential_energy);
			fprintf(energyfile, "\n");	
		}
		
		void writeVelocities(const double& velocity_x){
			// number_particles, cannot be stored in class,
			// since it my wary by one between the MPIs.
			// And all of the velocities must be printed from
			// world_rank == 0
			number_particles = velocity_x.size();
			for (int i=0; i<number_particles-1; i++){
				fprintf(velocityfile, "%f", velocity_x[i]);
				fprintf(velocityfile, "\n");
			}
		}
		
		void close_output_files(){
			fclose(energyfile);
			fclose(velocityfile);
		}
};
