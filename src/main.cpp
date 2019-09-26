#include "grid/grid.hpp"

#include <iostream>
#include <mpi.h>

int main(void)
{
    MPI_Init(NULL, NULL);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Get the name of the processor
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

    // Print off a hello world message
    std::cout << "Hello world from processor " << processor_name
              << ", rank " << world_rank << " out of " << world_size <<"processors" << std::endl;


    int nx = 10;
    int dim = 1;
    double xmin = 0.;
    double xmax = 1.;
    // Call custom library function
    Grid cond1d(dim, nx, xmin, xmax);

    cond1d.decomposeDomain();


    MPI_Finalize();
    return (0);
}
