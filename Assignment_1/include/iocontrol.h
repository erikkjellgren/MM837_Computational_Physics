
#include<vector>
#include<fstream>
#include<string>
#include"json.hpp"

using namespace std;
using json = nlohmann::json;

class print_results{
	FILE * energyfile;
	FILE * velocitydistributionfile;
	FILE * outputfile;
	int check_if_zero;
	public:
		print_results(const int& check_if_zero_){
			check_if_zero = check_if_zero_;
			if (check_if_zero==0){
				energyfile = fopen("energy.dat", "w");
				velocitydistributionfile = fopen("velocitydistribution.dat","w");
				outputfile = fopen("output.dat","w");
				
				fprintf(energyfile, "Time");
				fprintf(energyfile, " ");
				fprintf(energyfile, "Ekin");
				fprintf(energyfile, " ");
				fprintf(energyfile, "Epot");
				fprintf(energyfile, "\n");
				
				fprintf(velocitydistributionfile, "Velocity");
				fprintf(velocitydistributionfile, " ");
				fprintf(velocitydistributionfile, "Count");
				fprintf(velocitydistributionfile, "\n");
			}
		}
		
		
		void close_output_files(){
			fclose(energyfile);
			fclose(velocitydistributionfile);
			fclose(outputfile);
		}
		
		
		void checkInput(const int& world_size){
			double a, b, c, mass, delta;
			int number_particles, number_steps, print_frequency;
			// read in inputfile
			ifstream ifs("parameters.json");
			json j = json::parse(ifs);
			
			//write out input
			string s = j.dump(4);
			fprintf(outputfile, "Inputfile:");
			fprintf(outputfile, "\n");
			fprintf(outputfile, "%s", s.c_str());
			fprintf(outputfile, "\n");
			fprintf(outputfile, "Number of processes: ");
			fprintf(outputfile, "%d", world_size);
			fprintf(outputfile, "\n");
		}
		
		
		void writeEnergy(const double& kinetic_energy, const double& potential_energy, const double& time){
			fprintf(energyfile, "%f", time);
			fprintf(energyfile, " ");
			fprintf(energyfile, "%f", kinetic_energy);
			fprintf(energyfile, " ");
			fprintf(energyfile, "%f", potential_energy);
			fprintf(energyfile, "\n");	
		}
		
		
		void writeVelocityDistribution(const vector<long>& velocitydist, const double& max_velocity, const double& min_velocity){
			int bins = velocitydist.size();
			for (int i=0; i<bins-1; i++){
				fprintf(velocitydistributionfile, "%f", min_velocity+(max_velocity-min_velocity)/((double)bins)*(i+0.5));
				fprintf(velocitydistributionfile, " ");
				fprintf(velocitydistributionfile, "%ld", velocitydist[i]);
				fprintf(velocitydistributionfile, "\n");
			}
			fprintf(velocitydistributionfile, "Out-of-bounds ");
			fprintf(velocitydistributionfile, "%ld", velocitydist[bins-1]);
			fprintf(velocitydistributionfile, "\n");
		}
		
};
