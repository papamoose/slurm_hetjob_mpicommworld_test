#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>
#include <uuid/uuid.h>

#define UUID_STRING_LENGTH 36

void print_usage() {
    printf("Usage: mpiexec -n <num_ranks> ./test_mpi_comm_world [--debug]\n");
}

int main(int argc, char **argv) {
    int debug_mode = 0;

    // Check for command-line options
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "--help") == 0) {
            print_usage();
            return 0;
        } else if (strcmp(argv[i], "--debug") == 0) {
            debug_mode = 1;
        } // Add more options as needed
    }

    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    char generated_uuid[UUID_STRING_LENGTH + 1];

    if (rank == 0) {
        // Generate UUID on rank 0
        uuid_t uuid;
        uuid_generate(uuid);
        uuid_unparse_lower(uuid, generated_uuid);
        printf("Rank 0 generated UUID: %s\n", generated_uuid);
    }

    // Broadcast the UUID from rank 0 to all other ranks
    MPI_Bcast(generated_uuid, UUID_STRING_LENGTH + 1, MPI_CHAR, 0, MPI_COMM_WORLD);

    // non root ranks print the received UUID
    printf("Rank %d received UUID: %s\n", rank, generated_uuid);

    MPI_Finalize();
    return 0;
}
