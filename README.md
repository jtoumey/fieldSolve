# fieldSolve

Based on my work with `OpenFOAM`, this library exists for solving model problems in my coursework.

The code goes beyond the scope of what would typically suffice for these assignments in order to practice developing a flexible and modular flow solver.

## Compilation and Use
* To set the framework for parallel computation, use the MPI C++ compiler until the build system is ready.
  This compiler is a lightweight wrapper to the mpic compiler: `mpic++ main.cpp ...`
* To run on the macOs development environment, instruct MPI to allow additional tasks per hyperthread: `mpirun --use-hwthread-cpus -np num_procs ...`.
  Alternatively, run `mpirun --oversubscribe -np num_procs ...`
