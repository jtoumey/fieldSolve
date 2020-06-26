//
//  main.cpp
//  flowSolve
//
//  Created by Julian Toumey on 5/31/20.
//

#include "inputs.h"
#include "grid.h"
#include "field.h"

int main(int argc, const char * argv[])
{
    // Read input
    Inputs mainInput("main.inp");
    mainInput.parseInputFile();
    
    
    Grid fvGrid(&mainInput);
    fvGrid.discretize();
//    fvGrid.printGrid();
//    fvGrid.associateCellNeighbors();
    
    // Initialize a temperature field and write it to test
    double temperature0 = 298; // K
    Field<double> temperature(&fvGrid, temperature0);
    temperature.writeField();
    
}
