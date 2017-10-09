
#include<vector>

vector<double> getEnergy(const vector<double>& position_x, const vector<double>& velocity_x, const double& a, const double& b, const double& c, const double& mass, const int& world_rank, const int& world_size);
void binVelocities(const vector<double>& velocity_x, vector<long>& hist_velocity, const double& max_velocity, const double& min_velocity);