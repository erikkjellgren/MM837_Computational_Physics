/*****************************************************************************
 * iocontrol.h
 *
 * Controls the writing of output to files
 * ***************************************************************************/

#include<vector>
#include<fstream>
#include<string>
#include"json.hpp"

using namespace std;
using json = nlohmann::json;

class print_results{
	FILE* output_file;
	FILE* phi_file;
	int to_please_cpp;
	public:
		print_results(const int& to_please_cpp_){
			to_please_cpp = to_please_cpp_;
			output_file = fopen("output.dat","w");
			phi_file = fopen("phi.dat","w");
			fprintf(phi_file, "x;phi;delta_phi");
			fprintf(phi_file, "\n");
		}
		void close_files(){
			fclose(output_file);
			fclose(phi_file);
		}
		void write_input(){
			ifstream ifs("parameters.json");
			json j = json::parse(ifs);
			
			//write out input
			string s = j.dump(4);
			fprintf(output_file, "Inputfile:");
			fprintf(output_file, "\n");
			fprintf(output_file, "%s", s.c_str());
			fprintf(output_file, "\n");
			fprintf(output_file, "\n");
		}
		void write_property(const vector<double>& prop_value){
			fprintf(output_file, "\n");
			fprintf(output_file, "Normalization: ");
			fprintf(output_file, "%f", prop_value[0]);
			fprintf(output_file, "\n");
			fprintf(output_file, "<x>: ");
			fprintf(output_file, "%f", prop_value[1]);
			fprintf(output_file, "\n");
			fprintf(output_file, "<x**2>: ");
			fprintf(output_file, "%f", prop_value[2]);
			fprintf(output_file, "\n");
			fprintf(output_file, "<p>: ");
			fprintf(output_file, "%f", prop_value[3]);
			fprintf(output_file, "\n");
			fprintf(output_file, "<p**2>: ");
			fprintf(output_file, "%f", prop_value[4]);
			fprintf(output_file, "\n");
			fprintf(output_file, "<V>: ");
			fprintf(output_file, "%f", prop_value[5]);
			fprintf(output_file, "\n");
			fprintf(output_file, "<H>: ");
			fprintf(output_file, "%f", prop_value[6]);
			fprintf(output_file, "\n");
		}
		void write_phi(vector<double> x_value, vector<double> phi, vector<double> delta_phi){
			for (int i=1; i<phi.size()-1; i++){
				fprintf(phi_file, "%f", x_value[i]);
				fprintf(phi_file, ";");
				fprintf(phi_file, "%f", phi[i]);
				fprintf(phi_file, ";");
				fprintf(phi_file, "%f", delta_phi[i]);
				fprintf(phi_file, "\n");
			}
		}
		void write_iterations(const double& energy, const double& pn_right, const double& pn_left, const double& check, const double& delta_energy){
			fprintf(output_file, "Energy = ");
			fprintf(output_file, "%f",energy);
			fprintf(output_file, ", pn_right = ");
			fprintf(output_file, "%f",pn_right);
			fprintf(output_file, ", pn_left = ");
			fprintf(output_file, "%f",pn_left);
			fprintf(output_file, ", check = ");
			fprintf(output_file, "%f",check);
			fprintf(output_file, ", delta_energy = ");
			fprintf(output_file, "%f",delta_energy);
			fprintf(output_file, "\n");
		}
		void write_warning(const int& warning_code){
			if (warning_code==1){
				fprintf(output_file, "WARNING: check = check_old. No Newton-Raphson step was taken for this iteration.");
				fprintf(output_file, "\n");
			}
			else if (warning_code==2){
				fprintf(output_file, "WARNING: Energy didn't converge withing maximum number of iterations.");
				fprintf(output_file, "\n");
			}
		}
};