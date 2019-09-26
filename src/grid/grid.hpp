#ifndef GRID_HPP
#define GRID_HPP

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

    void discretize();
    void decomposeDomain();

};

#endif // GRID_HPP
