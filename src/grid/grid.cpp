#include "grid.hpp"

#include <mpi.h>

#include <iostream>

void Grid::discretize()
{
    for (int ii = 0; ii < num_elements; ++ii)
    {

    }
}

void Grid::decomposeDomain()
{
    // Find out rank, size
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int number;
    if (world_rank == 0) {
        number = -1;
        MPI_Send(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    } else if (world_rank == 1) {
        MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD,
                 MPI_STATUS_IGNORE);
        std::cout << "Process 1 received number " << number << " from process 0" << std::endl;
    }

}
