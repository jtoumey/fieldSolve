#ifndef GRID_HPP
#define GRID_HPP

#include "field.hpp"

class Grid
{
private:
    int dimension;
    int num_elements;
    double xmin, xmax;


public:
    Grid(int dim_, int num_elem_, double xmin_, double xmax_) :
         dimension(dim_),
         num_elements(num_elem_),
         xmin(xmin_),
         xmax(xmax_) {} ;

    void initializeField(int, T uniform_value);
    void discretize();
    void decomposeDomain();
    // Field registerField();

};

#endif // GRID_HPP
