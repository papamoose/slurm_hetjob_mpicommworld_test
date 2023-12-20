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

    if (size < 2) {
        fprintf(stderr, "This program requires at least 2 MPI ranks.\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    char generated_uuid[UUID_STRING_LENGTH + 1];
    if (rank == 0) {
        // Generate UUID on rank 0
        uuid_t uuid;
        uuid_generate(uuid);
        uuid_unparse_lower(uuid, generated_uuid);
        printf("Rank 0 generated UUID: %s\n", generated_uuid);

        // Broadcast the UUID to all other ranks
        MPI_Bcast(generated_uuid, UUID_STRING_LENGTH + 1, MPI_CHAR, 0, MPI_COMM_WORLD);
    } else {
        // Receive the UUID from rank 0
        MPI_Bcast(generated_uuid, UUID_STRING_LENGTH + 1, MPI_CHAR, 0, MPI_COMM_WORLD);
    }

    // Send the received UUID back to rank 0
    MPI_Send(generated_uuid, UUID_STRING_LENGTH + 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);

    // Rank 0 collects the results
    if (rank == 0) {
        int correct_count = 0;
        int incorrect_count = 0;

        for (int i = 1; i < size; ++i) {
            char received_uuid[UUID_STRING_LENGTH + 1];
            MPI_Recv(received_uuid, UUID_STRING_LENGTH + 1, MPI_CHAR, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            // Compare the received UUID with the generated one
            if (strcmp(generated_uuid, received_uuid) == 0) {
                correct_count++;
            } else {
                incorrect_count++;
            }

            // Print received UUID if in debug mode
            if (debug_mode) {
                printf("Rank %d received UUID: %s\n", i, received_uuid);
            }
        }

        printf("Results:\n");
        printf("Generated UUID: %s\n", generated_uuid);
        printf("Correct results: %d\n", correct_count);
        printf("Incorrect results: %d\n", incorrect_count);
    }

    MPI_Finalize();
    return 0;
}
