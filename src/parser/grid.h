//
//  grid.h
//  flowSolve
//
//  Created by Julian Toumey on 5/31/20.
//

#ifndef GRID_H
#define GRID_H

#include <vector>
#include <iostream>

#include "boundingBox.h"

#include "inputs.h"

/// Grid data to
struct GridData
{
    double x1Min, x1Max, x2Min, x2max, dx1, dx2;
    int x1Cells, x2Cells;
};

/// FlowSolve Coordinate
template <typename T>
class FsCoordinate
{
public:
    const int dimension = 2;
    T v1;
    T v2;
    
public:
    /// Constructor
    FsCoordinate(T v1_, T v2_) : v1(v1_), v2(v2_) {};
};

/// Grid Class: Holds the bounding box and geometrical coordinates
class Grid
{
private:
    
    BoundingBox domainBbox;
    
    // Num points per coordinate direction x_i
    int spatialDimension = 2; // Default to 2D
    int numCells[2];
    int numPoints[2];
    int totalCells;
    int totalPoints;
    double gridSpacing[2];
    
    std::vector<FsCoordinate<double>> pointCoordinates;
    std::vector<FsCoordinate<double>> cellCenCoordinates;
    
public:
    
    /// Constructor based on bounding box inputs
    Grid(Inputs* mainInputs_);
    
    /// Discretize the grid based on the bounding box and number of cells
    void discretize();
    
    /// Print the grid point coordinates to screen
    void printGrid();
    
    /// Link cell centers
    void associateCellNeighbors();
    
    /// Return grid size data
    GridData getGridData();
    
};

#endif /* GRID_H */
