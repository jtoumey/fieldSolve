#ifndef FIELD_HPP
#define FIELD_HPP

#include <vector>

template <typename T>
class Field
{
private:
    std::vector<double> field_quantity;

public:

    Field<T>(int size, T uniform_value)
    {
        field_quantity.assign(size, uniform_value);
    }

    double getFieldValue(int element_num)
    {
        double field_value = field_quantity[element_num];

        return(field_value);
    }


};

#endif // FIELD_HPP
