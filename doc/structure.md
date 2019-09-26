# Code Base Structure

Useful template for finite volume and finite differecne projects.


## Robust and flexible `field` class
* Methods for initialization--infinitely expandable
* A typical finite volume implementation would use a 1D array with index mapping
  + Store boundary ghost cells at the end of this array
  + A separate boundary conditions module makes application of varied BCs much easier, but one must maintain a mapping between the boundary cells in the `field` and the details of the BC

## Geometry Module
* Provide geometry tools

## Grid/Meshing Module

## Time Advancement Scheme
* Contain time integration methods

# Subset
A useful subset would be a library of functions for numerical solution of PDEs.
While this obviously exists, it would be nice to leverage my own code so as to show the professors that I understand the methods and developed them myself.
