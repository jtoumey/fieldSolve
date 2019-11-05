#ifndef GRID_HPP
#define GRID_HPP
#include "../framework/field.hpp"
#include <vector>

class Vertices
{
private:
    std::vector<double> x_coord;
    std::vector<double> y_coord;
public:
    Vertices();
    void addVertex(double xc_, double yc_)
    {
        x_coord.push_back(xc_);
        y_coord.push_back(yc_);
    }
};


class Grid
{
private:
    int dimension;
    std::vector<int> num_elements;
    std::vector<double> domain_extent;
    std::vector<double> element_size;

    // TODO: Develop geometric container
    // std::vector<double> vertex_coord;
    Vertices vertex_coords;
    std::vector<double> node_coord;


public:
    /* Constructor for one-d grid */
    Grid(int dim_, int num_elem_x_, double xmin_, double xmax_)
    {
        dimension = dim_;
        num_elements.push_back(num_elem_x_);
        domain_extent.push_back(xmin_);
        domain_extent.push_back(xmax_);
    }

    /* Constructor for two-d grid */
    Grid(int dim_, int num_elem_x_, int num_elem_y_, double xmin_, double xmax_, double ymin_, double ymax_)
    {
        dimension = dim_;
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

    /* Calculate vertices */
    // TODO: Implement as part of the geometry module
    void calculateVertices();

    /* Decompose domain for parallel solution */
    void decomposeDomain();
    // Field registerField();

    /* Require specific specializations of the templated class */
    friend class Field<int>;

    friend class Field<double>;

};

#endif // GRID_HPP
