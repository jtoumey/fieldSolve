#include <iostream>
#include <vector>

#include "framework/field.hpp"
#include "geometry/geometry.hpp"

int main(int argc, char* arg[])
{


    /*-- SIMPLE brute force code --*/
    // Here, we take the geometry explicitly

    const int npx = 4;
    const int npy = 4;
    double xmax = 1.0;
	double ymax = 1.0;

    /* Step 1: Initialize a simulation geometry */
    GeometryParameters box_geometry_parameters(xmax, ymax, npx, npy);
    Geometry box_geometry(box_geometry_parameters);


    double t0, t1, t_i, dt;
    t0 = 0.0;
    t1 = 1.0;
    dt = 1e-6;

    int t_n = 0;
    for (t_i = t0; t_i < t1; t_i += dt)
    {
        ++t_n;
        //std::cout << "Time-step number: " << t_n << " Simulation time: " << t_i << " Time-step size: " << dt << std::endl;
        //simpleAlgorithm.doTimeStep(dt);
        /*
        void Simple::doTimeStep(double dt)
        {

        }

        //simpleAlgorithm stores previous solution

        */

    }



    return 0;
}
