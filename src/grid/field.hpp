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

    /* Overload the subscript operator */
    T operator() (int i, int j)
    {
        int element_num = (i)*dimension[0] + j;
        // TODO: Compute num_elements for field in the constructor
        if (element_num >= num_elements || element_num < 0)
        {
            std::cout << "ERROR: Accessing invalid element in field." << std::endl;
            exit(0);
        }
        return (field_quantity[element_num]);
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
