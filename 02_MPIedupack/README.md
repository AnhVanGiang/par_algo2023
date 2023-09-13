# Examples from the book using MPI

If you prefer to directly use the broader MPI standard, the programs from the book are
also available using MPI. Note that these examples are **not maintained by the current course teachers**,
but they can be useful when working with the book while also trying to learn MPI.

On Snellius or your own Linux shell, you can download and extract the MPIedupack using
```bash
wget http://www.staff.science.uu.nl/~bisse101/Book/Edupack/MPIedupack1.0.tar
tar xf MPIedupack1.0.tar
``````

On Snellius, load the OpenMPI module like this:
```bash
module load 2023 OpenMPI/4.1.5-GCC-12.3.0
```
(if you put this line into your ${HOME}/.bashrc file, it will be automatically loaded in the future).

To compile the edupack, edit the Makefile and replace ``CC=cc`` by ``CC=mpicc``. Then type ``make``.

An example SLURM script is included in this directory on how to run the "inprod" example.
Submit it using ``sbatch ex1_innerproduct.slurm``, see your job in the queue using ``squeue``, and check
for the output file ``slurm-<jobid>``.
