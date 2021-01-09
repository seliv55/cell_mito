# Mitodyn
Version: 1.0

![Logo](RC.png)

## Short Description

Kinetic model of mitochondrial respiration linked with cellular energetic metabolism and glutamate transport in neurons

## Description

The software tool “Mitodyn”, coded in C++,  supports an analysis of dynamics of mitochondrial and cellular energy metabolism. It is based on a kinetic model, i.e., a system of ordinary differential equations (ODE) that describes mitochondrial electron transport, biochemical reactions providing substrates for the electron transport, oxidative phosphorylation, ATP consumption and transport of some metabolites through the cellular and inner mitochondrial membranes. It is customized for the neuronal cells.

## Key features

- Simulates time course of model variables, which are the concentrations of metabolites and redox states of respiratory complexes described by the ODE system, production of reactive oxygen species (ROS) separately in various sites of the electron transport chain. 
- Allows to program the change of rate constants and concentrations in the course of a calculation, which simulate specific experimental conditions.
- Enables continuous calculations of dependencies of the system steady states on model parameters. The latter can help to find bifurcation characteristics of the system.

## Approaches

- Kinetic modeling
    
## Data Analysis

- simulation of dynamics of oxygen consumption, reactive oxygen species (ROS) production, metabolite concentrations

## Tool Authors

- Vitaly Selivanov (Universitat de Barcelona)

## Git Repository

- https://github.com/seliv55/cell_mito

## Installation

- Mitodyn does not require installation. To run it in local computer it is sufficient to copy (clone) the repository and compile the code.
- The repository contains makefiles to compile the code using g++ compiler, which usually is installed by default in Linux operative systems. To use a different compiler the makefiles, which are located in root directory and other directories containing parts of the code ("con512tpl", "dasl", "integrT", "nrused") should be changed respectively.
- To compile the code the following command should be executed:
```
make clean && make 
```
- The compiler creates an executable binary file “mitodyn.out”. 

## Working with the program

- The repository has a script “mito.sh” that can be used to run Mitodyn.
- At runtime Mitodyn reads the input data: a file with initial values of the state variables and a file with the values of model parameters. Examples of input data, file with  the initial values of the state variables (“i1”) and the values of model parameters (“1”) are present in the repository.
- the paths to input files can be specified as default values in the script “mito.sh”, or as options in command line:
``` 
cd [Mitodyn directory]
./mito.sh -i i1 -p 1
```
- different input files can be used, but they should have the same format exemplified in "1" and "i1".
- Taking into consideration the large number of state variables (>300) and parameters (~70), it is recommended to start the first analysis using the presented example files.
- Mitodyn can run in various modes:
  * If mode = "0", Mitodyn makes a single simulation and stops;
  * If mode = "r", it also makes a single simulation but assuming inhibition of complex I by rotenone;
  * mode = "cont" produces a series of simulations incrementing a parameter in some interval starting from the point achieved in the previous simulation (shortened word "continuation").
    * In this mode Mitodyn reads an additional file "cont" that specifies the number of points in the series, the number of a chosen parameter in the array of parameters, the starting value of the parameter, and the interval's size. This file existing in the root directory contains an example of such specification.
  * mode = "rc" is the same as "cont" but assuming inhibition of complex I by rotenone.
- the disirable mode should be specified as default in "mito.sh", or as options in command line:
```
./mito.sh -m cont
```
- During the analysis the parameter values can be changed manually, running single simulations. The changed parameters can be saved in a different file and then used for subsequent analysis. The values of state variables obtained at the end of single simulation are saved in the file “i0” and then can be used as initial values for subsequent simulations.
- After performing a single simulation, Mitodyn saves the time course of variables of interest (mitochondrial membrane potential, Δψ), combinations of variables (e.g., sum of potentially ROS producing redox states) and functions of variables (oxygen consumption rate, VO<sub>2</sub>) in a text file “dynamics”.
- If GNUplot is installed, it plots the saved data executing the GNUplot script “gplt.p”, presented in the above mentioned directory. The plot is saved in the file “./kin/dynamics.png”.
- After running Mitodyn in the continuation mode, it saves the steady state values of the same variables and their combinations in the file “00000”, plots the dependence of selected steady state data executing the GNUplot script “gparplt.p”, and saves the plot “cont.png”.
- Here is an example of two single simulations:
```
./mito.sh
```
![two simulations](basic_var.png)
*Dynamics of some determinants of energy metabolism calculated by Mitodyn. Time course of Δψ (A), oxygen consumption (B), ubiquinol (QH2) content (C),  and ATP (D) are calculated for some basal state when ATP synthesis compensates its consumption (orange curves labeled as “work”) and ten-times decreased ATPase activity (blue curves labeled as “ROS”. The corresponding values of parameters and initial values of state variables are listed in the files “1” and “i1” respectively*

- Here is an example of two branches of stable steady states found by running Mitodyn in continuation mode:

![two branches](two_branches.png)
*Two branches of stable steady-states revealed by running Mitodyn in “cont” mode. The steady states for semiquinone at Qo site of complex III (A) and oxygen consumption (B) as functions of the parameter that reflects ATP demand. The stable steady-states branch obtained by simulations gradually decreasing the parameter is shown in orange. It is terminated by a limit point (LP), and further decrease of the parameter switches the system to the blue branch of stable steady-states. With subsequent increasing the parameter, the system remains in the blue branch of stable steady-states. Mitodyn does not locate the branch of unstable steady states situated between the orange and blue branches and connected with the orange branch in the limit point.*

## Publications

- Selivanov VA, Votyakova TV, Zeak JA, Trucco M, Roca J, Cascante M.
Bistability of mitochondrial respiration underlies paradoxical reactive oxygen
species generation induced by anoxia. PLoS Comput Biol. 2009 5(12):e1000619.

- Selivanov VA, Votyakova TV, Pivtoraiko VN, Zeak J, Sukhomlin T, Trucco M,
Roca J, Cascante M. Reactive oxygen species production by forward and reverse
electron fluxes in the mitochondrial respiratory chain. PLoS Comput Biol. 2011
7(3):e1001115.

- Selivanov VA, Cascante M, Friedman M, Schumaker MF, Trucco M, Votyakova TV.
Multistationary and oscillatory modes of free radicals generation by the
mitochondrial respiratory chain revealed by a bifurcation analysis. PLoS Comput
Biol. 2012 8(9):e1002700.
