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
    // Collect our information here as needed
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);



    int points_per_proc = num_elements/world_size;
    int start_pt = world_rank*points_per_proc;
    int end_pt = (world_rank + 1)*points_per_proc;

    /* Say we cannot divide tasks equally: we have at most three extra tasks,
       which we assign to the final proc
     */
    if (num_elements % world_size != 0)
    {
        if (world_rank == (world_size - 1))
        {
            std::cout << "Assigning" << num_elements%world_size << "extra tasks for proc"
                      << world_rank << std::endl;
            end_pt = end_pt + (num_elements % world_size);
        }
    }

    std::cout << "Np: " << num_elements << std::endl;
    std::cout << "Num procs: " << world_size << ", on rank: " << world_rank << std::endl;
    std::cout << "Np per proc:" << points_per_proc << std::endl;
    std::cout << "  Start pt:" << start_pt << ", end pt: " << (end_pt - 1) << std::endl;

    double* xc;
    xc = new double[num_elements];
    double dx = (xmax - xmin)/num_elements;

    for (int ii = start_pt; ii < end_pt; ++ii)
    {
        std::cout << "Rank " << world_rank << " computing pt " << ii << std::endl;
        xc[ii] = ii*dx + dx/2;
        std::cout << xc[ii] << std::endl;
    }


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
