#include <iostream>
#include <vector>

#include "grid/field.hpp"

int main(void)
{

    int num_elements = 11;
    double initial_pressure = 101325;
    double u0 = 1.5;

    Field pressure(num_elements, initial_pressure);
    Field velocity(num_elements, u0);

    // SIMPLE
    double u_0;
    double t, dt;
    t = 0;
    dt = 1e-4;

    for (int ii = 0; ii < num_elements; ++ii)
    {
        double u_n = velocity.getFieldValue(ii);

        u_0 = u_n + dt*(-u_);


    }




    return 0;
}
