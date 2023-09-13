#!/bin/bash
#SBATCH --ntasks=4
##SBATCH -t 00:01:00

# runs the inner product (ip) example using 4 processes
./BSPedupack/ip
