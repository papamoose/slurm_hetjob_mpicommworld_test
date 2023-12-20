## srun

Don't salloc or sbatch.

```
$ srun -N1 --overlap -n3 ./test_mpi_comm_world : -n3 ./test_mpi_comm_world | sort -k2n
srun: job 116 queued and waiting for resources
srun: job 116 has been allocated resources
Rank 0 generated UUID: ca53b144-a762-4cfc-89dc-47160a740420
Rank 0 received UUID: ca53b144-a762-4cfc-89dc-47160a740420
Rank 1 received UUID: ca53b144-a762-4cfc-89dc-47160a740420
Rank 2 received UUID: ca53b144-a762-4cfc-89dc-47160a740420
Rank 3 received UUID: ca53b144-a762-4cfc-89dc-47160a740420
Rank 4 received UUID: ca53b144-a762-4cfc-89dc-47160a740420
Rank 5 received UUID: ca53b144-a762-4cfc-89dc-47160a740420
```

## salloc -N1 : -N1
```
$ salloc -N1 : -N1
salloc: Pending job allocation 110
salloc: job 110 queued and waiting for resources
salloc: job 110 has been allocated resources
salloc: Granted job allocation 110
salloc: Nodes athena are ready for job

$ srun --het-group=0 -n3 ./test_mpi_comm_world : --het-group=1 -n3 ./test_mpi_comm_world | sort -k2n
Rank 0 generated UUID: 92e83ec9-746e-432e-9f3f-8e7cc28cf086
Rank 0 received UUID: 92e83ec9-746e-432e-9f3f-8e7cc28cf086
Rank 1 received UUID: 92e83ec9-746e-432e-9f3f-8e7cc28cf086
Rank 2 received UUID: 92e83ec9-746e-432e-9f3f-8e7cc28cf086
Rank 3 received UUID: 92e83ec9-746e-432e-9f3f-8e7cc28cf086
Rank 4 received UUID: 92e83ec9-746e-432e-9f3f-8e7cc28cf086
Rank 5 received UUID: 92e83ec9-746e-432e-9f3f-8e7cc28cf086
```

## sbatch



```
$ cat het.sb 
#!/bin/bash
#SBATCH --partition=cpu
#SBATCH -N1
#SBATCH hetjob
#SBATCH -N1

srun --het-group=0 -n3 ./test_mpi_comm_world : --het-group=1 -n3 ./test_mpi_comm_world


$ sbatch het.sb 

$ cat slurm-120.out
Rank 0 generated UUID: 11457598-914e-4010-b0b5-4b557693eea8
Rank 0 received UUID: 11457598-914e-4010-b0b5-4b557693eea8
Rank 1 received UUID: 11457598-914e-4010-b0b5-4b557693eea8
Rank 2 received UUID: 11457598-914e-4010-b0b5-4b557693eea8
Rank 3 received UUID: 11457598-914e-4010-b0b5-4b557693eea8
Rank 4 received UUID: 11457598-914e-4010-b0b5-4b557693eea8
Rank 5 received UUID: 11457598-914e-4010-b0b5-4b557693eea8
```


## sbatch that does not work

```
$ cat het.sb 
#!/bin/bash
#SBATCH --partition=cpu
#SBATCH -N1
#SBATCH hetjob
#SBATCH -N1

srun --het-group=0 -n3 ./test_mpi_comm_world &
srun --het-group=1 -n3 ./test_mpi_comm_world &
wait
```

```
$ cat slurm-122.out | sort -k2n
Rank 0 generated UUID: 2cd835a4-e199-4bec-9856-3f2a1fa6b239
Rank 0 generated UUID: 9e2e1095-6040-4b16-a5f7-a06442b1759e
Rank 0 received UUID: 2cd835a4-e199-4bec-9856-3f2a1fa6b239
Rank 0 received UUID: 9e2e1095-6040-4b16-a5f7-a06442b1759e
Rank 1 received UUID: 2cd835a4-e199-4bec-9856-3f2a1fa6b239
Rank 1 received UUID: 9e2e1095-6040-4b16-a5f7-a06442b1759e
Rank 2 received UUID: 2cd835a4-e199-4bec-9856-3f2a1fa6b239
Rank 2 received UUID: 9e2e1095-6040-4b16-a5f7-a06442b1759e
```
