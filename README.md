# README 

## High speed reactive flow solver in OpenFOAM® v2012 

### About the solver: ###
An OpenFOAM® based hybrid-central solver called **reactingPimpleCentralFoam** is validated to compute hydrogen-based detonations. The original version of this solver developed by Kraposhin et al is available here: https://github.com/unicfdlab/hybridCentralSolvers/tree/master/OpenFOAM-4.1/reactingPimpleCentralFoam. This solver is a pressure-based semi-implicit compressible flow solver based on central-upwind schemes of Kurganov and Tadmor, and possesses the features of standard OpenFOAM® solvers namely, rhoCentralFoam, reactingFoam and pimpleFoam. 

### Verification & validation: ###
We have validated an OpenFOAM® solver named reactingPimpleCentralFoam to perform hydrogen-oxygen-based (diluted with argon and nitrogen) detonation simulations, within the accuracy of the current state-of-the-art numerical simulations in open literature. The current study is devoted to: 
- careful verification and validation of the solver
- to provide appropriate guidelines on the necessary grid resolution to get converged solutions
- to implement efficient ways of computing the detonation structures.

In addition, we have made targeted enhancements on this solver:
* computing smoke foil field in shock-attached reference frame
* ZND based thermicity to quantify induction zone length in 2D simulations.

### Solver compilation: ###
All the instructions to compile the solver can be found in the solver folder.

### Simulation Execution Instructions:
Detailed guidelines for conducting the simulations can be found in the readme document located within the ***CaseFiles.tar.gz***, applicable to both 1D and 2D scenarios. Considering the constraints related to the size of the files, we have provided only a single case setup for each of the 1D and 2D simulations in this repository. For access to further case setups used in the paper, users are encouraged to reach out to us directly.
