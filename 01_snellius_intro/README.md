# My first Snellius Job

Supercomputers are shared among many users, and it is not permitted to run actual workloads on the login nodes.
They are intended for editing scripts and source code, and submitting jobs.

In this first example, look at the slurm script (``ex0_hello_world.slurm``), and submit it using
```bash
sbatch ex0_hello_world.slurm
```
Then use ``squeue`` to check the status of your job, and once it is finished (no longer appears in ``squeue``),
look at the output in ``slurm-<jobid>.out``. What happens if you change the flag ``--ntasks`` in the slurm script?
What if you change ``--cpus-per-task``?

To learn more about job submission and Snellius, see the [SURF Wiki](https://servicedesk.surf.nl/wiki/display/WIKI/HPC+User+Guide).



