
#include <iostream>


extern "C" void sub_(int* fsize, double* fvec, double* fsum);


int main (int argc, char** argv)
{

    int i, size;
    double sum;
    double* vec;

    size = 5000;
    vec = new double[size];

    for (i = 0; i < size; i++)
    {
        vec[i] = 1.1234532;
    }
    sub_(&size, vec, &sum);

    std::cout << "sum = " << sum << std::endl;

    delete[] vec;
}
