#include <iostream>
#include <vector>

#include "grid/field.hpp"

int main(void)
{

    /*-- SIMPLE brute force code --*/
    // GRID
    const int npx = 8;
    const int npy = 8;
    double xmax = 1.0;
	double ymax = 1.0;

    // INITIAL FIELDS
    double init_pres = 101325;
    double init_dens = 1.0;
    double init_velocity = 1.5;

    // TODO: The enum is not necessary here
    Field<double> pressure(TWO_D, npx, npy, init_pres);
    Field<double> velocity(TWO_D, npx, npy, init_velocity);

    

    return 0;
}
