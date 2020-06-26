#include <iostream>
#include <vector>
#include <string>

#include <cassert>

//template<unsigned int DIMENSION>
class DoubleVector2d
{
private:
    double components[2];
public:

    DoubleVector2d(double componentOne_, double componentTwo_)
    {
        components[0] = componentOne_;
        components[1] = componentTwo_;
    }

    double& operator[](int index) // overloading the []
    {
        assert(index < 2);
        assert(index > -1);
        return(components[index]);
    }
};

struct Boundary
{
    std::string boundaryName;
    int boundaryStart;
    int boundaryEnd;
};

class Grid
{
private:

public:
    int numPoints;

};

// class BoundaryConditions
// {
// private:
//
// public:


// };
template <class T>
class Field
{
private:
    int fieldSize;
    std::vector<int> fieldDimensions;

    // std::unique_ptr<double[]> fieldData;
    std::vector<T> fieldData;

    std::vector<Boundary> boundaryList;


public:
    /* Default ctor */
    Field() : fieldSize(0) {};

    /* Preferred ctor with field initialization */
    Field(int fieldSizeX_, int fieldSizeY_, T initialValue_)
    {
        fieldDimensions.push_back(fieldSizeX_);
        fieldDimensions.push_back(fieldSizeY_);
        fieldSize = fieldSizeX_*fieldSizeY_;

        fieldData.assign(fieldSize, initialValue_);

        // segregateBoundaries();
    }

    void initialize(int fieldSizeX_, int fieldSizeY_, T initialValue_)
    {
        fieldDimensions.push_back(fieldSizeX_);
        fieldDimensions.push_back(fieldSizeY_);
        fieldSize = fieldSizeX_*fieldSizeY_;

        fieldData.assign(fieldSize, initialValue_);
    }

    int calculateGlobalIndex(int xIdx_, int yIdx_)
    {
        int globalIdx = (xIdx_)*fieldDimensions[1] + yIdx_;
        if (globalIdx >= fieldSize || globalIdx < 0)
        {
            std::cout << "ERROR: Accessing invalid element in field." << std::endl;
            exit(0);
        }
        return (globalIdx);
    }

    /* Overload the function call operator for two-D fields */
    double operator() (int xIdx_, int yIdx_)
    {
        int globalIdx = calculateGlobalIndex(xIdx_, yIdx_);
        return (fieldData[globalIdx]);
    }

    void setElement(int xIdx_, int yIdx_, T elementValue_)
    {
        int globalIdx = calculateGlobalIndex(xIdx_, yIdx_);
        fieldData[globalIdx] = elementValue_;
    }

    // void operator= (double fieldElement_)
    // {
    //     int globalIdx = (xIdx_)*fieldDimensions[1] + yIdx_;
    //     fieldData[globalIdx] = fieldElement_;
    //
    // }

    /* Split out boundary patches  */
    void segregateBoundaries()
    {
        Boundary xMin;
        Boundary xMax;
        // boundary

    }
    //
    // void setBoundaryConditions()

};

class Solver
{
private:

public:
    void solve()
    {
        /* March along x-direction */
        for (int xIdx = 0; xIdx < grid.numPoints; ++xIdx)
        {

        }
    }
}

class Simulation
{
private:
    /* Simulation has-a grid */
    Grid grid;

    /* Simulation has-a solver */
    Solver explicitSolver;

    /* Simulation has-a field */
    /* TODO: Refactor to set of fields */
    Field<DoubleVector2d> velocityField;
    Field<DoubleVector2d> velocityFieldTm1;

public:
    /* ctor */
    // Simulation();
    void initializeGrid()
    {
        const int numPoints = 100;
        grid.numPoints = numPoints;
    }
    /* */
    void initializeFields()
    {
        DoubleVector2d initVelocity(1.0, 0.0);
        velocityField.initialize(grid.numPoints, grid.numPoints, initVelocity);
        velocityFieldTm1.initialize(grid.numPoints, grid.numPoints, initVelocity);

        /* Generate an initial velocity profile */
        int xIdx = 0;
        double yod;
        double UE = 1.0;
        int mEst = 21;
        int fM1 = mEst = 1;
        for (int yIdx = 2; yIdx < mEst; ++yIdx)
        {
            yod = (float(yIdx) - 1)/fM1;
            DoubleVector2d velProfile(UE*(1.5*yod - 0.5*yod*yod*yod), 0.0);
            velocityFieldTm1.setElement(xIdx, yIdx, velProfile);
        }
    }

    void setBoundaryConditions()
    {
        /* Loop over wall boundary, enforcing no-slip BC */
        int yIdx = 0;
        DoubleVector2d tempVel(0.0, 0.0);
        for (int xIdx = 0; xIdx < grid.numPoints; ++xIdx)
        {
            velocityField.setElement(xIdx, yIdx, tempVel);
            velocityFieldTm1.setElement(xIdx, yIdx, tempVel);
        }
    }

    /* Run the simulation */
    void run()
    {
        initializeGrid();
        initializeFields();
        setBoundaryConditions();
        explicitSolver.solve();
    }

};


int main (void)
{
    Simulation boundaryLayer2D;
    boundaryLayer2D.run();


    // field.setBoundaryConditions(bConds);
    // void setBoundaryConditions(BoundaryConditions)
    // {
    //     for patch in patchList:
    //         patchData = *bConds.getPatchData(patch)
    //         for ii = patch.start..patch.end:
    //             field[ii] = patchData.value
    // }


    std::vector<double> U, U0, V, V0;

    double XI = 1.0;
    double XF = 2.0;

    double CNU = 0.0002;
    double UINF = 10;
    int MMAX = 100;
    double DY = 0.00112;
    double RE = UINF*1.0/CNU;

    double X = XI;
    double DELT = 0.0224;
    double DELST = 0.00771;
    double THETA = 0.00297;
    double CF = 0.00297;

    double UE = 1.0;
    double DUEDX = -0.05;

    for (int ii = 1; ii < MMAX; ++ii)
    {
        U.push_back(UE);
        U0.push_back(UE);
        V.push_back(0.0);
        V0.push_back(0.0);
    }
    U[1] = 0.0;
    U0[1] = 0.0;

    int MEST = 21;
    int FM1 = MEST - 1;
    for (int ii = 2; ii < MEST; ++ii)
    {
        double YOD = (float(ii) - 1)/FM1;
        std::cout << "YOD: " << YOD << std::endl;
        U0[ii] = UE*(1.5*YOD - 0.5*YOD*YOD*YOD);
    }

    while (X < XF)
    {
        double DX = 0.4*U0[2]*DY*DY*RE;
        if ((X + DX) > XF)
        {
            DX = XF - X;
        }
        X = X + DX;

        UE = 1.05 - X/20.0;
        DUEDX = -0.05;

        U0[MMAX] = UE;

        double ST = 0.5;
        double TA = 0.0;

        /* Explicit scheme */
        double A, B, C, H, H1, F1, F2;
        for (int M = 2; M < MMAX - 1; ++M)
        {
            A = 1.0/RE - V0[M]*DY/2.0;
            B = 1.0/RE + V0[M]*DY/2.0;
            C = UE*DUEDX*DY*DY - 2.0*U0[M]/RE;
            H1 = 0.5*DY/DX;
            H = DX/(U0[M]*DY*DY);
            U[M] = U0[M] + H*(A*U0[M + 1] + B*U0[M - 1] + C);
            std::cout << "U[" << M << "]: " << U[M] << std::endl;
            V[M] = V[M - 1] - H1*(U[M] - U0[M] + U[M - 1] - U0[M - 1]);

            F1 = 1.0 - U[M]/UE;
            F2 = F1*U[M]/UE;
            ST = ST + F1;
            TA = TA + F2;
        }

        DELST = DELST*DY;
        THETA = THETA*DY;

        for (int M = 1; M < MMAX; ++M)
        {
            if (U[M] > 0.99*UE)
            {
                MEST = M;
            }
        }
        DELT = (MEST - 1)*DY;

        CF = (4.0*U[2] - U[3])/(UE*UE*DY*RE);

        if (CF < 0.0001)
        {
            std::cout << "Near separation at X = " << X << std::endl;
        }
        std::cout << "[" << X << "\t" << DELT << "\t" << DELST << "\t" << THETA
                  << CF << "\t" << UE << "\t" << DUEDX << "]" << std::endl;
        for (int M = 2; M < MMAX; ++M)
        {
            U0[M] = U[M];
            V0[M] = V[M];
        }
    }

    /* */

    return (0);
}
