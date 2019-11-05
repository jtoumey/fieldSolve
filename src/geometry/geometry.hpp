#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include <vector>

struct GeometryParameters
{
    double x, y;
    int nx, ny;

    GeometryParameters(double x_, double y_, int nx_, int ny_) :
        x(x_), y(y_), nx(nx_), ny(ny_) {}
};

struct Node
{
    double x, y;
    int neighbors[4] = {-1, -1, -1, -1};
    int edge_neighbors[4] = {-1, -1, -1, -1};
};

struct Edge
{
    int start_vertex;
    int end_vertex;
    int cell_neighbors[2] = {-1, -1};
};

struct UniqueEdgeStatus
{
    int unique_neighbor;
    int neighbor_count;
};

class Geometry
{
private:
    /* The parameters struct for initialization */
    GeometryParameters geometry_params;

    /* Generic geometry information */
    int num_points;
    // TODO: Remove hard-coded value
    double x_min = 0.0;
    double y_min = 0.0;
    double x_max, y_max;

    int num_points_x, num_points_y;
    int num_verts;

    double dx, dy;

    std::vector<Node> vertices;
    std::vector<Node> cell_centers;
    std::vector<Edge> edge_list;

public:

    /*  */
    Geometry(GeometryParameters inputs_) : geometry_params(inputs_)
    {
        /* Initialize the geometry by computing all salient parameters */
        x_max = geometry_params.x;
        y_max = geometry_params.y;

        num_points_x = geometry_params.nx;
        num_points_y = geometry_params.ny;

        num_points = geometry_params.nx*geometry_params.ny;
        num_verts = (geometry_params.nx + 1)*(geometry_params.ny + 1);

        dx = geometry_params.x/(float)(geometry_params.nx);
        dy = geometry_params.y/(float)(geometry_params.ny);

        calculateVertices();
        calculateCellCenters();
        calculateConnectivity();

        generateEdgeList();
        writeEdgeList();
        determineCellEdgeAssociation();
    }

    /* TODO: This could all be packaged into one task */
    /* Methods for grid calculation */
    void calculateVertices();
    void calculateCellCenters();
    void calculateConnectivity();

    /* Methods for edge list generation */
    void generateEdgeList();
    UniqueEdgeStatus findUniqueFaceNeighbors(int, int, int);
    void determineCellEdgeAssociation();

    void writeEdgeList();
};

#endif // GEOMETRY_HPP
