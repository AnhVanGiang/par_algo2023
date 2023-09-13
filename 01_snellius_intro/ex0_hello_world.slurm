#!/bin/bash

# estimated runtime needed (careful, if you underestimate, your job gets killed!)
#          hh:mm:ss
#SBATCH -t 00:01:00
# number of processes to start (each process may run on a different node)
#SBATCH --ntasks=1
# number of cores available to each process (if your application uses multiple threads)
#SBATCH --cpus-per-task=1

# The srun command makes sure that the processes are started on the reserved CPU cores.
# In this example, the "application" is the linux builtin command "hostname".
# What happens if you request multiple tasks? What if you explicitly specify "SBATCH --nodes=1"?
# What if you use one task but multiple "cpus-per-task"?
srun  hostname
