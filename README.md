# Mitodyn
Version: 1.0

![Logo](RC.png)

## Short Description

Kinetic model of mitochondrial respiration linked with cellular energetic metabolism and glutamate transport in neurons

## Description

The software tool “Mitodyn” supports an analysis of mitochondrial and cellular energy metabolism dynamics. It is based on a kinetic model, i.e., a system of ordinary differential equations (ODE) that describes mitochondrial electron transport, biochemical reactions providing substrates for the electron transport, oxidative phosphorylation, ATP consumption and transport of some metabolites through the cellular and inner mitochondrial membranes. It is customized for the neuronal cells.

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

- Mitodyn does not require installation. To run it in local computer it is sufficient to copy (clone) the repository. 
- If some of .cpp or .h files are modified, run 
``` make clean && make 
```
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
