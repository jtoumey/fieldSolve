//
//  field.h
//  flowSolve
//
//  Created by Julian Toumey on 5/31/20.
//

#ifndef FIELD_H
#define FIELD_H

#include <vector>
#include <iostream>

class Grid;

template <typename T>
class Field
{
private:
    int numCells;
    std::vector<T> fieldElements;
    
    Grid* assocGrid;
    
public:
    
    /// Constructor: Set initial value 
    Field(Grid* assocGrid_, double initialValue_)
    {
        GridData cg = assocGrid_->getGridData();
        numCells = cg.x1Cells*cg.x2Cells;
        for (int ii = 0; ii < numCells; ++ii)
        {
            fieldElements.push_back(initialValue_);
        }
    }
    
    /// Destructor:
//    ~Field();
    
    /// Member functions
    void writeField()
    {
        std::cout << "Index \t Cell Value\n";
        for (int ii = 0; ii < numCells; ++ii)
        {
            std::cout << "Index: " << ii << "\t" << fieldElements[ii]
                      << std::endl;
        }
    }
};

#endif /* FIELD_H */
