/*****************************************************************************
 * iocontrol.cc
 * Contains methods to print outputs to files
 * ***************************************************************************/
 
#include<fstream>
#include<string>
#include"json.hpp"

using namespace std;
using json = nlohmann::json;

class print_results{
	FILE* output_file;
	int to_please_cpp;
	public:
		print_results(const int& to_please_cpp_in){
			to_please_cpp = to_please_cpp_in;
			output_file = fopen("output.dat","w");
		}
		void close_files(){
			fclose(output_file);
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
		void fatal_error(const int& error_code){
			if (error_code == 1){fprintf(output_file, "FATAL ERROR: No valid sweeping method was chosen");}
			// If fatal error close all files
			close_files();
		}
};