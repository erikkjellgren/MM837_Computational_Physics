
#include<vector>

using namespace std;

void update_position(vector<double>& position_x, const vector<double>& velocity_x, const double& integration_step);
void update_velocity(vector<double>& velocity_x, const vector<double>& acceleration_x, const double& integration_step);