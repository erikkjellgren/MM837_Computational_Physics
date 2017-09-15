#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

class ParticleCircle{
	private:
		double radius, omega, x, y, delta_time, time;
		std::ofstream outfile;
		const double pi=3.14159265358979323846;
	public:
		void set_values(const double& r, const double& w, const double& dt){
			radius     = r;
			omega      = w;
			delta_time = dt;
			time       = 0.0;
			outfile.open("output"+std::to_string(w)+".txt");
		}
		void propagate(){
			time = time + delta_time;
			x      = radius*std::cos(time*omega);
			y      = radius*std::sin(time*omega);
		}
		void write_xy(){
			outfile << x << ' ' << y << ' ' << '\n';
		}
		void close_file(){
			outfile.close();
		}
		void get_completed_circles(){
			std::cout << "Circle distances moved: " << std::fmod(time*omega, 2.0*pi) << '\n';
		}
};

int main(){
	ParticleCircle PC;
	ParticleCircle PC2;
	PC.set_values(1.0, 2.7, 1.0);
	PC2.set_values(1.0, 3.1, 0.7);
	for (int i=0; i<100; i++){
		PC.propagate();
		PC.write_xy();
		PC2.propagate();
		PC2.write_xy();
	}
	PC.get_completed_circles();
	PC2.get_completed_circles();
	PC.close_file();
	PC2.close_file();
	return 0;
}