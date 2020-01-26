#ifndef FINITEDIFFERENCEGRIDHEADERDEF
#define FINITEDIFFERENCEGRIDHEADERDEF
#include <vector>
#include "node.hpp"

class FiniteDifferenceGrid
{
public:
    // The boundary value class is able to // access the nodes
    friend class BvpOde;
private:
    std::vector<Node> mNodes;
public:
    FiniteDifferenceGrid(int numNodes, double xMin,
                         double xMax);
};

#endif // FINITEDIFFERENCEGRIDHEADERDEF
