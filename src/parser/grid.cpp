//
//  grid.cpp
//  flowSolve
//
//  Created by Julian Toumey on 6/17/20.
//

#include "grid.h"

#include <cmath>

Grid::Grid(Inputs* mainInputs_)
{
    domainBbox.x1Min = mainInputs_->domainBbox.x1Min;
    domainBbox.x1Max = mainInputs_->domainBbox.x1Max;
    domainBbox.x2Min = mainInputs_->domainBbox.x2Min;
    domainBbox.x2Max = mainInputs_->domainBbox.x2Max;
    
    numCells[0] = mainInputs_->x1Cells;
    numCells[1] = mainInputs_->x2Cells;
    numPoints[0] = numCells[0] + 1;
    numPoints[1] = numCells[1] + 1;
    
    totalCells = numCells[0]*numCells[1];
    totalPoints = numPoints[0]*numPoints[1];
}

void Grid::discretize()
{
    // Calculate fixed grid spacing
    double dx1 = (domainBbox.x1Max - domainBbox.x1Min)/(double)numCells[0];
    double dx2 = (domainBbox.x2Max - domainBbox.x2Min)/(double)numCells[1];
    
    gridSpacing[0] = dx1;
    gridSpacing[1] = dx2;
    
    // Build point list
    for (int ii = 0; ii < numPoints[0]; ++ii)
    {
        for (int jj = 0; jj < numPoints[1]; ++jj)
        {
            const double x1 = domainBbox.x1Min + ii*dx1;
            const double x2 = domainBbox.x2Min + jj*dx2;
            
            pointCoordinates.push_back(FsCoordinate<double>(x1, x2));
        }
    }
    
    // Build cell center list
    for (int ii = 0; ii < numCells[0]; ++ii)
    {
        for (int jj = 0; jj < numCells[1]; ++jj)
        {
            const double x1 = domainBbox.x1Min + dx1/2.0 + ii*dx2;
            const double x2 = domainBbox.x2Min + dx2/2.0 + jj*dx2;
            
            cellCenCoordinates.push_back(FsCoordinate<double>(x1, x2));
        }
    }
}

void Grid::printGrid()
{
    std::cout << " == POINT LIST == " << std::endl;
    std::cout << " Point ID \t (x1, x2) " << std::endl;
    for (int ii = 0; ii < numPoints[0]; ++ii)
    {
        for (int jj = 0; jj < numPoints[1]; ++jj)
        {
            int cellIdx = ii*(numPoints[1]) + jj;
            std::cout << " " << cellIdx << "\t"
            << "(" << pointCoordinates[cellIdx].v1 << ", "
            << pointCoordinates[cellIdx].v2 << ")" << std::endl;
        }
    }
    
    std::cout << " == Cell Center LIST == " << std::endl;
    std::cout << " Cell ID \t (xc1, xc2) " << std::endl;
    for (int ii = 0; ii < numCells[0]; ++ii)
    {
        for (int jj = 0; jj < numCells[1]; ++jj)
        {
            int cellIdx = ii*(numCells[1]) + jj;
            std::cout << " " << cellIdx << "\t"
            << "(" << cellCenCoordinates[cellIdx].v1 << ", "
            << cellCenCoordinates[cellIdx].v2 << ")" << std::endl;
        }
    }
}

void Grid::associateCellNeighbors()
{
    double eps = 0.0000000001;

    // Loop over all cells, treating each as the parent
    for (int ii = 0; ii < numCells[0]*numCells[1]; ++ii)
    {
        double x1Parent = cellCenCoordinates[ii].v1;
        double x2Parent = cellCenCoordinates[ii].v2;

        // Loop over all cell to find neighbors 
        for (int jj = 0; jj < numCells[0]*numCells[1]; ++jj)
        {
            double x1Child = cellCenCoordinates[jj].v1;
            double x2Child = cellCenCoordinates[jj].v2;

            double x1Diff = fabs(x1Parent - x1Child);
            double x2Diff = fabs(x2Parent - x2Child);

            /* Test if the difference in the y-direction between cell centers
             * is essentially equal to the grid spacing dy */
            double x1DiffDx = fabs(x1Diff - gridSpacing[0]);
            double x1DiffSign = x1Parent - x1Child;
            double x2DiffDy = fabs(x2Diff - gridSpacing[1]);
            double x2DiffSign = x2Parent - x2Child;

            /* If the cell is within the tolerance of another cell, assign appropriately */
            if (x1Diff < eps)
            {
                if (x2DiffDy < eps && x2DiffSign > 0)
                {
                    std::cout << "South cell match: parent idx " << ii << " with child " << jj << std::endl;
                    //nodes[ii].neighbors[0] = jj;
                }
                else if (x2DiffDy < eps && x2DiffSign < 0)
                {
                    std::cout << "North cell match: parent idx " << ii << " with child " << jj << std::endl;
                    //nodes[ii].neighbors[2] = jj;
                }
            }
            if (x2Diff < eps)
            {
                if (x1DiffDx < eps && x1DiffSign > 0)
                {
                    std::cout << "West cell match: parent idx " << ii << " with child " << jj << std::endl;
//                    nodes[ii].neighbors[3] = jj;
                }
                else if (x1DiffDx < eps && x1DiffSign < 0)
                {
                    //std::cout << "East cell match: parent idx " << ii << " with child " << jj << std::endl;
//                    nodes[ii].neighbors[1] = jj;
                }
            }
        }
    }
}

GridData Grid::getGridData()
{
    GridData currentGrid;
    currentGrid.x1Min = domainBbox.x1Min;
    currentGrid.x1Max = domainBbox.x1Max;
    currentGrid.x2Min = domainBbox.x2Min;
    currentGrid.x2Min = domainBbox.x2Max;
    currentGrid.x1Cells = numCells[0];
    currentGrid.x2Cells = numCells[1];
    currentGrid.dx1 = gridSpacing[0];
    currentGrid.dx2 = gridSpacing[1];
    return (currentGrid);
}
