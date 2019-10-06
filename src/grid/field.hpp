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
    Dimension domain_dimension;
    std::vector<double> dimension;
    int num_elements;

    std::vector<double> field_quantity;
public:


    Field<T>(int size, T uniform_value)
    {
        domain_dimension = ONE_D;
        dimension.push_back(size);
        field_quantity.assign(size, uniform_value);
        calcNumElements();
    }
    Field<T>(int row, int col, T uniform_value)
    {
        domain_dimension = TWO_D;
        dimension.push_back(row);
        dimension.push_back(col);
        field_quantity.assign(row*col, uniform_value);
        calcNumElements();
    }

    /* Overload the function call operator */
    T operator() (int x_idx, int y_idx)
    {
        int global_idx = (x_idx)*dimension[0] + y_idx;
        if (global_idx >= num_elements || global_idx < 0)
        {
            std::cout << "ERROR: Accessing invalid element in field." << std::endl;
            exit(0);
        }
        return (field_quantity[global_idx]);
    }

    void calcNumElements()
    {
        num_elements = 1;
        for (int ii = 0; ii < dimension.size(); ++ii)
        {
            num_elements = num_elements*dimension[ii];
        }
    }
};

#endif // FIELD_HPP
