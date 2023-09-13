# Examples from the book using MPI

If you prefer to stay close to the book and use BSPlib, you first need to install a version of the library.
We recommend the [MultiCore BSP for C](http://www.multicorebsp.com/) implementation, which is suitable for
one node of Snellius (128 cores).

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
export PATH=${HOME}/MultiCoreBSP-for-C/tools/:${PATH}
```
Add this line to the file ``~/.bashrc`` to make it available automatically after every login.

## BSPedupack

This is a collection of BSP examples from the book by Rob Bisseling. After installing either of the BSPlib variants above,
it is a good idea to install the edupack to get started.

```bash
wget https://webspace.science.uu.nl/~bisse101/Book2/BSPedupack2.0.tar.gz
tar xzvf BSPedupack2.0.tar.gz
```
