
#include<vector>
#include<fstream>
#include<string>

using namespace std;

class print_results{
	FILE * energyfile, velocityfile, outputfile;
	public:
		print_results(){
			energyfile = fopen("energy.txt", "w");
			velocityfile = fopen("velocities.txt","w");
			outputfile = fopen("output.txt","w");
		}
		
		
		void close_output_files(){
			fclose(energyfile);
			fclose(velocityfile);
			fclose(outputfile);
		}
		
		
		void checkInput(const int& world_size){
			double a, b, c, mass, delta;
			int number_particles, number_steps, print_frequency;
			// read in inputfile
			ifstream ifs("parameters.json");
			json j = json::parse(ifs);
			
			//write outinput
			string s = j.dump(4);
			fprintf(outputfile, "Inputfile:");
			fprintf(outputfile, '\n');
			fprintf(outputfile, "%s", s.c_str());
			fprintf(outputfile, '\n');
			fprint(outputfile, "Number of processes: ");
			fprint(outputfile, "%d", world_size);
			fprintf(outputfile, '\n');
			fclose(outputfile);
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
};
