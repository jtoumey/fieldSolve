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

    std::vector<double> field_entries;
public:

    /* Constructor for a one-D field */
    Field(int, T);

    /* Constructor for a two-D field */
    Field(int, int, T);

    /* Overload the function call operator for one-D fields */
    T operator() (int idx)
    {
        // Cannot supply two arguments for a one-D field
        if (domain_dimension == TWO_D)
        {
            std::cout << "ERROR: Supplying too few arguments for accessing a two-D field." << std::endl;
            exit(0);
        }

        if (idx >= num_elements || idx < 0)
        {
            std::cout << "ERROR: Accessing invalid element in field." << std::endl;
            exit(0);
        }
        return (field_entries[idx]);
    }

    /* Overload the function call operator for two-D fields */
    T operator() (int x_idx, int y_idx)
    {
        // Cannot supply two arguments for a one-D field
        if (domain_dimension == ONE_D)
        {
            std::cout << "ERROR: Supplying too many arguments for accessing a one-D field." << std::endl;
            exit(0);
        }

        int global_idx = (x_idx)*dimension[0] + y_idx;
        if (global_idx >= num_elements || global_idx < 0)
        {
            std::cout << "ERROR: Accessing invalid element in field." << std::endl;
            exit(0);
        }
        return (field_entries[global_idx]);
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
