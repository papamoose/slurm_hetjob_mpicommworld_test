all:
	mpicc test_mpi_comm_world.c -o test_mpi_comm_world -luuid

clean:
	rm -f test_mpi_comm_world
