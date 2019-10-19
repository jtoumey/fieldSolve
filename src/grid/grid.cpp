#include "grid.hpp"

#include <mpi.h>
#include <iostream>

void Grid::discretizeDomain()
{
    double dx = (domain_extent[1] - domain_extent[0])/num_elements[0];
    double dy = (domain_extent[3] - domain_extent[2])/num_elements[1];
    element_size.push_back(dx);
    calculateVertices();
}

void Grid::calculateVertices()
{
    double xc = 0.0;
    double yc = 0.0;

    for (int ii = 0; ii < (num_elements[0] + 1); ++ii)
    {
        for (int jj = 0; jj < (num_elements[1] + 1); ++jj)
        {
            vertex_coords.addVertex(xc, yc);
            yc += element_size[1];
        }
        xc += element_size[0];
        yc = 0.0;
    }
}


void Grid::decomposeDomain()
{
    // Collect our world information here as needed
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int points_per_proc = num_elements[0]/world_size;
    int start_pt = world_rank*points_per_proc;
    int end_pt = (world_rank + 1)*points_per_proc;

    /* Say we cannot divide tasks equally: we have at most three extra tasks,
       which we assign to the final proc
     */
    int leftover_tasks = num_elements[0] % world_size;

    if (leftover_tasks != 0)
    {
        if (world_rank < (leftover_tasks))
        {
            start_pt = world_rank*(points_per_proc + 1);
            end_pt = (world_rank + 1)*points_per_proc + world_rank + 1;
        }
        else
        {
            start_pt = world_rank*(points_per_proc + 1);
            end_pt = start_pt + (points_per_proc);
        }
    }

    // std::cout << "Np: " << num_elements << std::endl;
    std::cout << "Num procs: " << world_size << ", on rank: " << world_rank << std::endl;
    std::cout << "Np per proc:" << points_per_proc << std::endl;
    std::cout << "  Start pt:" << start_pt << ", end pt: " << (end_pt - 1) << std::endl;

    double* xc;
    xc = new double[num_elements[0]];
    double dx = (domain_extent[1] - domain_extent[0])/num_elements[0];

    for (int ii = start_pt; ii < end_pt; ++ii)
    {
        std::cout << "Rank " << world_rank << " computing pt " << ii << std::endl;
        xc[ii] = ii*dx + dx/2;
        //std::cout << xc[ii] << std::endl;
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
