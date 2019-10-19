#ifndef GRID_HPP
#define GRID_HPP

class Vertices
{
    std::vector<double> x_coord;
    std::vector<double> y_coord;

    Vertices();
};

// #include "../framework/field.hpp"

class Grid
{
private:
    int dimension;
    std::vector<int> num_elements;
    std::vector<double> domain_extent;

    // TODO: Develop geometric container
    std::vector<double> vertex_coord;
    std::vector<double> node_coord;


public:
    /* Constructor for one-d grid */
    Grid(int dim_, int num_elem_x_, double xmin_, double xmax_) :
         dimension(dim_),
    {
        num_elements.push_back(num_elem_x_);
        domain_extent.push_back(xmin_);
        domain_extent.push_back(xmax_);
    }

    /* Constructor for two-d grid */
    Grid(int dim_, int num_elem_x_, int num_elem_y_, double xmin_, double xmax_, double ymin_, double ymax_) :
         dimension(dim_),
    {
        num_elements.push_back(num_elem_x_),
        num_elements.push_back(num_elem_y_),
        domain_extent.push_back(xmin_);
        domain_extent.push_back(xmax_);
        domain_extent.push_back(ymin_);
        domain_extent.push_back(ymax_);
    }

    // void initializeField(int, T uniform_value);
    /* Generate grid containers */
    void discretizeDomain();

    /* Decompose domain for parallel solution */
    void decomposeDomain();
    // Field registerField();

    /* Require specific specializations of the templated class */
    friend class Field<int>;

    friend class Field<double>;

};

#endif // GRID_HPP
