
#include<vector>
#include<fstream>
#include<string>
#include"../external/json.hpp"

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
				energyfile = fopen("energy.txt", "w");
				velocitydistributionfile = fopen("velocitydistribution.txt","w");
				outputfile = fopen("output.txt","w");
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
		
		
		void writeEnergy(const double& kinetic_energy, const double& potential_energy){
			fprintf(energyfile, "%f", kinetic_energy);
			fprintf(energyfile, " ");
			fprintf(energyfile, "%f", potential_energy);
			fprintf(energyfile, "\n");	
		}
		
		
		void writeVelocityDistribution(){
			
		}
		
};
