#!/bin/bash
#SBATCH --ntasks=4
##SBATCH -t 00:01:00

# prepare the environment: this makes your runs
# reproducible (independent of currently loaded modules when submitting)
module load 2022 OpenMPI/4.1.4-GCC-11.3.0

# runs the inner product (ip) example using 4 processes
# and a vector length of N=1M
echo 1000000 > input.tmp
srun -n 4 ./MPIedupack/ip < input.tmp
