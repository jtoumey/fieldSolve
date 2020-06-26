#include <iostream>
#include <mpi.h>

#include <cmath>

int main (int argc, char* argv[])
{
    MPI_Init(&argc, &argv);
    MPI_Status status;

    int numProcs, procId;
    MPI_Comm_size(MPI_COMM_WORLD, &numProcs);
    MPI_Comm_rank(MPI_COMM_WORLD, &procId);
 

    /* Send the data from rank 0 */
    int tag = 30;
    if (procId == 0)
    {
        std::cout << "Rank " << procId << " sending..." << std::endl;
        double sendBuffer[2] = {100.0, 200.0};
        MPI_Send(&sendBuffer, 2, MPI_DOUBLE, 1, tag, MPI_COMM_WORLD);
    }

    /* Receive the data on rank 1 */
    if (procId == 1)
    {
        std::cout << "Rank " << procId << " receiving..." << std::endl;
        double recvBuffer[2] = {0.0, 0.0};
        MPI_Recv(recvBuffer, 2, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
    
        for (int ii = 0; ii < 2; ++ii)
        {
            std::cout << recvBuffer[ii] << std::endl;
        }
    }

    int maxN = 1000;
    double sum = 0.0;

    for (int nn = procId; nn < maxN; nn += numProcs)
    {
        double temp = 1.0/(2.0*(double(nn)) + 1.0);

        // nn is even
        if (nn % 2 == 0)
        {
            sum += temp;
        }
        // nn is odd
        else
        {
            sum -= temp;
        }
    }

    double globalSum;
    MPI_Reduce(&sum, &globalSum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (procId == 0)
    {
        std::cout << "Pi is approx. " << 4.0*globalSum << " with error "
                  << 4.0*globalSum - M_PI << std::endl;
    }

    MPI_Finalize();
    return (0);
}

