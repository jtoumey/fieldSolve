#include "field.hpp"

template <typename T>
Field<T>::Field(int num_elements, T uniform_value)
{
    domain_dimension = ONE_D;
    dimension.push_back(num_elements);
    field_entries.assign(num_elements, uniform_value);
    calcNumElements();
}

template <typename T>
Field<T>::Field(int num_elements_x, int num_elements_y, T uniform_value)
{
    domain_dimension = TWO_D;
    dimension.push_back(num_elements_x);
    dimension.push_back(num_elements_y);
    field_entries.assign(num_elements_x*num_elements_y, uniform_value);
    calcNumElements();
}

/* Workaround for splitting template class header and implementation */
template class Field<int>;
template class Field<double>;
