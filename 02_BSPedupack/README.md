# Examples from the book using BSPlib

If you prefer to stay close to the book and use BSPlib, you first need to install a version of the library.
We recommend the [MultiCore BSP for C](http://www.multicorebsp.com/) implementation, which is suitable for
one node of Snellius (128 cores).

**Caveat:** On Snellius, only the Multi-Core implementation works reliably, and only if you
request a full node (128 cores). In order not to waste too many resources, please develop
your programs on another platform (e.g. your laptop) or run very short/small tests on the login node.

## Getting and compiling the BSPlib

- Download the source code on Snellius (or in your own linux shell): 
```bash
wget http://www.multicorebsp.com/downloads/c/2.0.4/MulticoreBSP-for-C.tar.xz
```
- unpack using
```bash
tar xJf MulticoreBSP-for-C.tar.xz
```
To compile the library, change to the extracted directory and type ``make``:
```bash
$ cd MulticoreBSP-for-C/
$ make
```

To make the compiler command ``bspcc`` available in your terminal, type
```bash
export PATH=${HOME}/MulticoreBSP-for-C/tools/:${PATH}
```
Add this line to the file ``~/.bashrc`` to make it available automatically after every login.

## BSPedupack

This is a collection of BSP examples from the book by Rob Bisseling. After installing either of the BSPlib variants above,
it is a good idea to install the edupack to get started.

```bash
wget https://webspace.science.uu.nl/~bisse101/Book2/BSPedupack2.0.tar.gz
tar xzvf BSPedupack2.0.tar.gz
```

## Running an example on Snellius

To compile, again go to the unpacked directory and type ``make``.
The job script ``ex1_innerproduct.slurm`` is ready to be submitted after you compiled the BSPedupack.
To do so, use
```bash
$ sbatch ex1_innerproduct.slurm
```
You can check the job status with the command ``squeue``.
Once finished, the job no longer appears in ``squeue``, and 
the output will be in a file called ``slurm-<jobid>.out``.

**Note**: if you look in the job script, it requests 128 "cpus-per-task". This is a full node,
whereas only 4 cores are actually used by the program (as read from the input file). 
This is for technical reasons on Snellius. If you have a program that you want to test
for different numbers of cores, you can run them one after the other in the same job script.
For testing and developing, just run the program on the login node (using ``./bspinprod <``.
This also allows you to specify p and n interactively.

**Note**: The bsprun command is not required to start your program. On Snellius, always use ``srun`` to run on compute
nodes, or no prefix to run on the login node.

**Guideline**: anything up to 8 cores and less than a minute of runtime should be OK for the login nodes, or develop
your code on your laptop and go to Snellius only for benchmarks.
