# Variants of the inner product algorithm

Here you can practice implementing your first algorithm in MPI or BSPlib.
As before, we want to compute the inner product of two vectors, and your
task is to implement a different variant of the "reduction" step that combines
all local results to the final sum.

We provide two working programs (``mpi_inprod.c`` and ``bsp_inprod.c``),
choose whichever programming model you prefer.

Read the programs to undersstand their structure,
and then add your own code in locations marked by ``/* ... YOUR CODE ...*/``.

On Snellius, don't forget to oad the MPI module:
```bash
module load 2022 OpenMPI/4.1.4-GCC-11.3.0
```

Compile using either ``make bsp`` or ``make mpi``.

For testing, run teh BSP code using
```bash
./bsp_inprod.x 4 1000
```
and the MPI code using
srun -n 4 ./mpi_inprod.x 1000
```
Where 4 is the number of processors (cores) to use,
and n=1000 is the vector length.

``srun`` will submit the job to the queue, so you may have to wait for some time.
When working on your own system, or to run **very small** tests on the login-node on Snellius,
replace ``srun -n`` by``mpirun -np``.

