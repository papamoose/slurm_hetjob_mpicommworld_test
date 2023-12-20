## srun

Don't salloc or sbatch.

```
$ srun -N1 --overlap -n2 ./test_mpi_comm_world_v2 --debug : -n2 ./test_mpi_comm_world_v2
srun: job 88 queued and waiting for resources
srun: job 88 has been allocated resources
Rank 0 generated UUID: b396b5d9-8221-455e-846c-52b28de28b5f
Rank 1 received UUID: b396b5d9-8221-455e-846c-52b28de28b5f
Rank 2 received UUID: b396b5d9-8221-455e-846c-52b28de28b5f
Rank 3 received UUID: b396b5d9-8221-455e-846c-52b28de28b5f
Results:
Generated UUID: b396b5d9-8221-455e-846c-52b28de28b5f
Correct results: 3
Incorrect results: 0
```

## salloc -N1 : -N1
```
kauffman2@hades:~$ salloc -N1 : -N1
salloc: Pending job allocation 90
salloc: job 90 queued and waiting for resources
salloc: job 90 has been allocated resources
salloc: Granted job allocation 90
salloc: Nodes athena are ready for job
kauffman2@athena:~$ srun --het-group=0 -n1 ./test_mpi_comm_world_v2 --debug : --het-group=1 -n1 ./test_mpi_comm_world_v2
Rank 0 generated UUID: 2c659f8c-1ce5-4286-a65c-b7656d593f9c
Rank 1 received UUID: 2c659f8c-1ce5-4286-a65c-b7656d593f9c
Results:
Generated UUID: 2c659f8c-1ce5-4286-a65c-b7656d593f9c
Correct results: 1
Incorrect results: 0
```
