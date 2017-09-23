#include <mpi.h>
#include <iostream>

double f(const double x){
	return x*x;
}

double trapezintegration(const double a, const double b, const double n){
	"a = start value of integration range";
	"b = end value of integration range";
	"n = number of integration slices";
	double integral=0.0, h=(b-a)/n;
	long loopbound = (long)n;
	"integral = the value of the numeric integral";
	"h        = width of the numeric integration";
	integral = -(f(a)+f(b))/2.0;
	for (long i=1;i<=loopbound;i++){
		integral = integral + f(a+i*h);
	}
	integral = integral*(b-a)/n;
	return integral;
}


int main(){
	// The MPI enviroment need to be initialized
	MPI_Init(NULL, NULL);
	
	// The program need to know how many processors that are avaible
	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	
	// The processors index is also needed to be known
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	
	// Now the execution of the program can be done

	// If no processor index (rank) is specfied the code will be 
	// executed for all the processes
	
	const double a=0.0, b=15.0, n=1e+10;
	double integral, total_integral;
	
	// Right now all of the processes have the same a and b
	// now different a and b will be assigned to the processes
	
	// The rank is the index of the processor going from
	// 0 to WORLD_SIZE-1, all of the processes will now get
	// different local_a and local_b
	
	double local_a = (b - a)/world_size*world_rank;
	double local_b = (b - a)/world_size*(world_rank+1);
	double local_n = n/world_size;
	
	integral = trapezintegration(local_a, local_b, local_n);
	
	// All of the processes have now run the numerical integration
	// for their given interval. All of the integrated parts need
	// to be collected to get the total integration.
	// Lets collect the result in Rank 0
	
	// if rank is different from rank 0, the result need to be send
	if (world_rank != 0){
		// To send the integral MPI_send need the following information:
		// a refrence to the value (&integral)
		// the amount of packages send
		// The type (MPI_DOUBLE)
		// The rank of the reciever
		// A uniqie tag
		// MPI_COMM_WORLD
		MPI_Send(&integral,1,MPI_DOUBLE,0,555+world_rank,MPI_COMM_WORLD);
	}
	if (world_rank == 0){
		// Setting the total integral equal to the integral calculated
		// by rank 0
		total_integral = integral;
		for (int i=1; i<world_size; i++){
				// To recieve the information the following information is needed:
				// a refrence to the value (&integral)
				// the amount of packages recieved
				// The type (MPI_DOUBLE)
				// The rank of the sender
				// The uniqie tag of the packages
				// MPI_COMM_WORLD
				// MPI_STATUS_IGNORE
				MPI_Recv(&integral,1,MPI_DOUBLE,i,555+i,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
				// after recieving the integral, add it to the total integral
				total_integral = total_integral + integral;
		}
		
	}
	
	// print out the result, from rank 0
	if (world_rank == 0){
		std::cout << total_integral << '\n';
	}
	
	// The MPI enviroment need to be closed when the calculation is finished
	MPI_Finalize();
}