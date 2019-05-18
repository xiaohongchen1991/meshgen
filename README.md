# Release versions

version 1.0.0:

A set of C++ APIs are provided to mimic the same behaviors as the MATLAB function "linspace" and "meshgrid".

# Quick start

This is a simple C++ library used to generate mesh grid. Function "linspce" is used to generate 1D evenly spaced numbers over a specified interval and "meshgrid" is used to generate 2D or 3D uniform Cartesian mesh grid. The usage of these two APIs mimic the behaviors of the corresponding MATLAB functions.

## Basics

    #include "meshgrid.hpp"
    #include <vector>

meshgen::linspace accepts forward iterator as inputs. To generate evenly spaced numbers over a specified interval, do:

    std::vector<double> v1(6);
    // starting point
    double x1 = 0.0;
    double h = 0.1;
    meshgen::linspace(v1.begin(), v1.end(), x1, h);

meshgen::linspace can also accept "number of points" as the input. e.g.

    const N = 6;
    double v2[N];
    // starting point
    double x1 = 0.0;
    // ending point
    double x2 = 0.5;
    meshgen::linspace(v2, v2 + 6, x1, x2, N);

There is also a function overload to mimic the same interface of the MATLAB function linspace:

    const N = 6;
    // starting point
    double x1 = 0.0;
    // ending point
    double x2 = 0.5;
    std::vector<double> v = meshgen::linspace(x1, x2, N);

The meshgen::meshgrid generates 2D or 3D uniform Cartesian meshgrid. The return type of this function is a template class:

    // T:  value type  
    // D:  which dimension, 0 for x, 1 for y, 3 for z
    // ND: number of dimensions, 2 for 2D, 3 for 3D
    template<class T, std::size_t D, std::size_t ND>
    class mesh_grid;

This data structure "mesh_grid" internally only stores a 1D array to minimize the memory cost. To create a mesh grid, do:

    // MATLAB usage
    std::vector<double> x(1);
    x[0] = 0.0;
    std::vector<double> y(2);
    y[0] = 0.1;
    y[1] = 0.2;
    std::vector<double> z(2);
    z[0] = 0.3;
    z[1] = 0.4;
    meshgen::mesh_grid<double, 0, 3> X;
    meshgen::mesh_grid<double, 1, 3> Y;
    meshgen::mesh_grid<double, 2, 3> Z;
    std::tie(X, Y, Z) = meshgen::meshgrid(x, y, z);

    // or use iterators to initialize mesh grid
    std::vector<double> x(1);
    x[0] = 0.0;
    std::vector<double> y(2);
    y[0] = 0.1;
    y[1] = 0.2;
    meshgen::mesh_grid<double, 0, 2> X;
    meshgen::mesh_grid<double, 1, 2> Y;
    std::tie(X, Y) = meshgen::meshgrid(x.begin(), x.end(), y.begin(), y.end());

The generated mesh_grid can be traversed in the following way:

    # include <iostream>
    for (size_t i = 0; i < X.size1(); ++i) {
        for (size_t j = 0; j < X.size2(); ++j) {
            for (size_t k = 0; k < X.size3(); ++k) {
                std::cout << "x coordinate = " << X(i, j, k) << "\n";
            }
        }
    }

## Exceptions

Exceptional situations throw C++ exceptions. There are two types of exceptions: std::invalid_argument and std::domain_error. When input arguments are invalid, std::invalid_argument is thrown with message "bad argument". When mesh_grid is accessed by a out-of-range index, std::domain_error is thrown with message "bad size".

## Linking

This is a header only library.

## Requirements

The library only requires a C++ compiler that supports C++14.
