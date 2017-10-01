

void NaiveEuler(double& position_x, double& velocity_x, double& acceleation_x, const double& integration_step){
	// position_x, postion of the particle
	// velocity_x, velocity of the particle
	// acceleation_x, acceleration of the particle
	// integration_step, stepsize taking in the integration
	double x_new, v_new;
	x_new = position_x + integration_step*velocity_x;
	v_new = velocity_x + integration_step*acceleation_x;
	
	position_x = x_new;
	velocity_x = v_new;
}