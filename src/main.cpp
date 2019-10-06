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
    double init_velocity_u = 1.5;
    double init_velocity_v = 2.0;

    Field<double> pressure(npx, npy, init_pres);
    Field<double> vel_u(npx, npy, init_velocity_u);
    Field<double> vel_v(npx, npy, init_velocity_v);

    Field<double> density(npx, npy, init_dens);


    // OUTER LOOP--SIMPLE PRESSURE-VELOCITY COUPLING (STEADY-STATE)

    // Loop over interior cells--momentum equation
    // _e.g._, calcMomentumFlux()

    for (int ii = 1; ii < (npx - 1); ++ii)
    {
        for (int jj = 1; jj < (npy - 1); ++jj)
        {
            double u_P = vel_u(ii, jj);
            double v_P = vel_v(ii, jj);

            double u_W = vel_u(ii - 1, jj);
            double u_E = vel_u(ii + 1, jj);
            double v_S = vel_v(ii, jj - 1);
            double v_N = vel_v(ii, jj + 1);

            // Interpolate cell face flux via central difference
            double F_w = 0.5*(u_W + u_P)*density(ii, jj);
            double F_e = 0.5*(u_P + u_E)*density(ii, jj);
            double F_s = 0.5*(v_P + v_S)*density(ii, jj);
            double F_n = 0.5*(v_P + v_N)*density(ii, jj);
        }
    }

    std::cout << vel_u(-1, 4);
    return 0;
}
