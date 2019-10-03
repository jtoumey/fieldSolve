#ifndef FIELD_HPP
#define FIELD_HPP

#include <vector>
#include <iostream>

enum Dimension
{
    ONE_D,
    TWO_D
};

template <typename T>
class Field
{
private:
    std::vector<double> field_quantity;
    Dimension domain_dimension;
    std::vector<double> dimension;

public:

    Field<T>(Dimension domain_dim_, int size, T uniform_value)
    {
        domain_dimension = domain_dim_;
        dimension.push_back(size);
        field_quantity.assign(size, uniform_value);

    }
    Field<T>(Dimension domain_dim_, int row, int col, T uniform_value)
    {
        domain_dimension = domain_dim_;
        dimension.push_back(row);
        dimension.push_back(col);
        field_quantity.assign(row*col, uniform_value);

    }

    /* One-dimensional case */
    double getFieldValue(int element_num)
    {
        double field_value = field_quantity[element_num];
        return(field_value);
    }
    /* Function overload for two-dimensional case */
    double getFieldValue(int row, int col)
    {
        int element_num = (row)*dimension[0] + col;

        double field_value = field_quantity[element_num];
        return(field_value);
    }


};

#endif // FIELD_HPP
