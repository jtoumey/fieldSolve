#include <iostream>
#include <vector>
#include <cmath>

class Field;
class Grid;

class Field
{
private:
    int np;

    std::vector<double> field_values;

    // pointer to the grid from which this was created. That way,
    // other functions can get the grid spacing
    Grid& reference_grid;

public:
    Field(int np_, Grid& reference_grid_) : reference_grid(reference_grid_)
    {
        np = np_;
        // reference_grid = reference_grid_;
    }

    void initializeField(double initial_value_)
    {
        for (int ii = 0; ii < np; ++ii)
        {
            field_values.push_back(initial_value_);
        }
    }

    double getFieldElement(int ii)
    {
        if (ii < 0 || ii > np)
        {
            std::cout << "Invalid access.";
        }
        return(field_values[ii]);
    }

    int getFieldSize()
    {
        return(np);
    }

    void printField()
    {
        std::cout << "[";
        for (int ii = 0; ii < np; ++ii)
        {
            std::cout << field_values[ii];
            if (ii < np -1)
            {
                std::cout << ", ";
            }
        }
        std::cout << "]" << std::endl;
    }

    double getSpacing(int, int);

};

class Grid
{
private:
    const double x_min = 0.0;
    int np;
    double x_max;
    double dx;

    std::vector<double> nodes;
    std::vector<double> centers;

public:
    Grid(int np_, double x_max_)
    {
        np = np_;
        x_max = x_max_;
        dx = (x_max - x_min)/float(np_);
        std::cout << "delta_x: " << dx << std::endl;
    }

    void calculateNodes()
    {
        for (int ii = 0; ii < (np + 1); ++ii)
        {
            double node_coordinate = ii*dx;
            std::cout << node_coordinate << std::endl;
            nodes.push_back(node_coordinate);
        }
    }

    void calculateCellCenters()
    {
        for (int ii = 0; ii < np; ++ii)
        {
            double dx_half = dx/2.0;
            double center_coordinate = float(ii)*dx + dx_half;
            centers.push_back(center_coordinate);
        }
    }

    int getNodes()
    {
        return(np);
    }

    double getSpacing(int x0_, int x1_)
    {
        if (x0_ < 0 || x1_ < 0 || x0_ > np || x1_ > np)
        {
            std::cout << " Invalid access " << std::endl;
        }
        std::cout << "[" << x0_ << " -> " << x1_ << "]" << std::endl;

        double spacing = nodes[x1_] - nodes[x0_];
        if (spacing < 1e-16)
        {
            std::cout << "Calculated grid spacing is too close to zero. Div by zero may occur." << std::endl;
            exit(0);
        }
        std::cout << "Spacing " << spacing << std::endl;
        return(std::abs(spacing));
    }

};

double Field::getSpacing(int x0_, int x1_)
{
    if (x0_ < 0 || x1_ < 0 || x0_ > np || x1_ > np)
    {
        std::cout << " Invalid access " << std::endl;
    }
    std::cout << "[" << x0_ << " -> " << x1_ << "]" << std::endl;

    double spacing = reference_grid.getSpacing(x1_, x0_);//- reference_grid.getSpacing(x0_);
    if (spacing < 1e-16)
    {
        std::cout << "Calculated grid spacing is too close to zero. Div by zero may occur." << std::endl;
        exit(0);
    }
    std::cout << "Spacing " << spacing << std::endl;
    return(std::abs(spacing));
}

// class LinearSystem
// {
// private:
//     int np;
//     std::vector<
//
//
// public:
//     LinearSystem(Grid& grid_)
//
// };

namespace fdm
{
    double div(Field& field_)
    {
        std::vector<double> div_calculation;

        int field_size = field_.getFieldSize();
        for (int ii = 1; ii < field_size - 1; ++ii)
        {
            double x_c;
            x_c = field_.getFieldElement(ii);
            std::cout << "=> " << ii << ", " << x_c << std::endl;

            double x_p1 = field_.getFieldElement(ii + 1);
            std::cout << "xp1" << x_p1;
            double x_m1 = field_.getFieldElement(ii - 1);
            double dx = field_.getSpacing(ii - 1, ii + 1);
            double div_calc = (x_p1 - x_m1)/dx;
            std::cout << div_calc;
            div_calculation.push_back(div_calc);
        }

        return(2.0);
    }
}

int main(void)
{
    double x_max = 1.0;
    int np = 4;

    Grid grid_1d(np, x_max);
    grid_1d.calculateNodes();

    Field temperature(grid_1d.getNodes(), grid_1d);
    double t_0 = 294; // Kelvin
    temperature.initializeField(t_0);

    temperature.printField();

    double div_test = fdm::div(temperature);

    std::cout << "Div: " << div_test << std::endl;



    return 0;
}
