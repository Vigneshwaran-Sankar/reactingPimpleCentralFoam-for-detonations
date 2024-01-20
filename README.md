## High-speed reactive flow solver in OpenFOAM® v2012 

[![GitHub release](https://img.shields.io/badge/release-v1.0.0-blue)](https://github.com/Vigneshwaran-Sankar/reactingPimpleCentralFoam-for-detonations/tree/master)
[![OpenFOAM](https://img.shields.io/badge/OpenFOAM-v2012-blue)](https://www.openfoam.com/news/main-news/openfoam-v20-12)

## Solver description: ##
An OpenFOAM®-based hybrid central solver called **reactingPimpleCentralFoam** is validated to compute hydrogen-based detonations. The original version of this solver was developed by [Kraposhin et al.](https://github.com/unicfdlab/hybridCentralSolvers/tree/master/OpenFOAM-4.1/reactingPimpleCentralFoam). This solver is a pressure-based semi-implicit compressible flow solver based on central-upwind schemes of Kurganov and Tadmor that possesses the features of standard OpenFOAM® solvers namely, rhoCentralFoam, reactingFoam, and pimpleFoam. 

## Verification & validation: ###
We have validated an OpenFOAM® solver named reactingPimpleCentralFoam to perform hydrogen-oxygen-based (diluted with argon and nitrogen) detonation simulations within the accuracy of the current state-of-the-art numerical simulations in the open literature. The current study is devoted to: 
- careful verification and validation of the solver
- to provide appropriate guidelines on the necessary grid resolution to get converged solutions
- to implement efficient ways of computing the detonation structures.

In addition, we have made targeted enhancements to this solver by implementing the computation of:
* Smoke foil field in the shock-attached reference frame
* ZND-based thermicity to quantify induction zone length in 2D simulations.

## Prerequisites: ###
The solver in this repository is tested and validated using ESI version [OpenFOAM® v2012](https://www.openfoam.com/news/main-news/openfoam-v20-12).

## Solver compilation: ###
The solver folder in this repository contains all the instructions to compile the solver.

## Simulation Execution Instructions: ###
Detailed guidelines for conducting the simulations can be found in the readme document located within the ***CaseFiles.tar.gz***, applicable to both 1D and 2D scenarios. Considering the constraints related to the size of the files, we have provided only a single case setup for each of the 1D and 2D simulations in this repository. For access to further case setups used in the paper, users are encouraged to reach out to us directly.

## How to cite: ###
1. Vigneshwaran Sankar, Karl P. Chatelain, Josué Melguizo-Gavilanes, Deanna A. Lacoste, 2024. Validation of High Speed Reactive Flow Solver in OpenFOAM with Detailed Chemistry. OpenFOAM® Journal.
