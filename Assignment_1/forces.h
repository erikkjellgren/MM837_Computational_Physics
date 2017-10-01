

double polynomicForce(const double& position_x1, const double& position_x2, const double& a, const double& b, const double& c){
	// position_x1, x coodinate of particle i
	// position_x2, x coordinate of particle i+1
	double Force=0.0;
	if (a != 0.0){Force += a*(position_x1 - position_x2);}
	if (b != 0.0){Force += b*(position_x1 - position_x2)*(position_x1 - position_x2);}
	if (c != 0.0){Force += c*(position_x1 - position_x2)*(position_x1 - position_x2)*(position_x1 - position_x2);}
	return Force;
}
