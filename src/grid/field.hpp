#ifndef FIELD_HPP
#define FIELD_HPP

#include <vector>


class Field
{
private:
    std::vector<double> field_quantity;

public:
    Field(int, double);
    double getFieldValue(int);


};

#endif // FIELD_HPP
