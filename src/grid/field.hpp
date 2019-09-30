#ifndef FIELD_HPP
#define FIELD_HPP

#include <vector>

// Enum for creation method

template <typename T>
class Field
{
private:
    std::vector<T> field_quantity;

public:
    void initialize(T uniform_value);
    void initialize(T uniform_value, int flag);



};

#endif // FIELD_HPP
