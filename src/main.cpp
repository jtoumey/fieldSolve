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

    /* Hide these, they are carryover from my old connectivity library */
    box_geometry_parameters.np = box_geometry_parameters.nx*box_geometry_parameters.ny;
    box_geometry_parameters.num_verts = (box_geometry_parameters.nx + 1)*(box_geometry_parameters.ny + 1);
    box_geometry_parameters.dx = box_geometry_parameters.x/(float)(box_geometry_parameters.nx);
    box_geometry_parameters.dy = box_geometry_parameters.y/(float)(box_geometry_parameters.ny);

    Geometry box_geometry(box_geometry_parameters);

    box_geometry.calculateVertices();
    box_geometry.calculateCellCenters();
    box_geometry.calculateConnectivity();

    box_geometry.generateEdgeList();
    box_geometry.writeEdgeList();
    box_geometry.determineCellEdgeAssociation();


    double dx = xmax/npx;
    double dy = xmax/npy;



    return 0;
}
