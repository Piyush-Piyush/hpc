#include <iostream>
#include <mpi.h>
using namespace std;

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    int world_size, world_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Define a 2D Cartesian topology
    int dims[2] = {2, 2};    // 2x2 grid (for simplicity)
    int periods[2] = {0, 0}; // No periodic boundaries
    int reorder = 1;         // Allow MPI to reorder ranks for efficiency

    MPI_Comm cart_comm;
    MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periods, reorder, &cart_comm);

    if (cart_comm != MPI_COMM_NULL)
    {
        int coords[2];
        MPI_Cart_coords(cart_comm, world_rank, 2, coords);
        cout << "Process " << world_rank << " has coordinates (" << coords[0] << ", " << coords[1] << ")\n";

        // Find neighbors in each direction
        int left, right, up, down;
        MPI_Cart_shift(cart_comm, 0, 1, &up, &down);    // Shift in row direction
        MPI_Cart_shift(cart_comm, 1, 1, &left, &right); // Shift in column direction

        cout << "Process " << world_rank
             << " neighbors: left=" << left
             << ", right=" << right
             << ", up=" << up
             << ", down=" << down << "\n";
    }

    MPI_Finalize();
    return 0;
}
