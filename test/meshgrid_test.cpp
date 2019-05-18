#include "meshgrid.hpp"

#include <vector>
#include <tuple>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using ::testing::ElementsAreArray;
using ::testing::DoubleEq;

TEST(TestLinspace, InputWithStepSize)
{
    std::vector<double> ret1(6, 0.0);
    double x1 = 0.0;
    double h = 0.1;
    meshgen::linspace(ret1.begin(), ret1.end(), x1, h);
    EXPECT_THAT(ret1, ElementsAreArray({DoubleEq(0.0),
                    DoubleEq(0.1),
                    DoubleEq(0.2),
                    DoubleEq(0.3),
                    DoubleEq(0.4),
                    DoubleEq(0.5)}));
    double ret2[6];
    meshgen::linspace(ret2, ret2 + 6, x1, h);
    EXPECT_THAT(ret2, ElementsAreArray({DoubleEq(0.0),
                    DoubleEq(0.1),
                    DoubleEq(0.2),
                    DoubleEq(0.3),
                    DoubleEq(0.4),
                    DoubleEq(0.5)}));
}

TEST(TestLinspace, InputWithNumPts)
{
    std::vector<double> ret1(6, 0.0);
    double x1 = 0.0;
    double x2 = 0.5;
    double h = 0.1;
    size_t N = static_cast<size_t>((x2 - x1)/h) + 1;
    meshgen::linspace(ret1.begin(), x1, x2, N);
    EXPECT_THAT(ret1, ElementsAreArray({DoubleEq(0.0),
                    DoubleEq(0.1),
                    DoubleEq(0.2),
                    DoubleEq(0.3),
                    DoubleEq(0.4),
                    DoubleEq(0.5)}));
    double ret2[6] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    meshgen::linspace(ret2, x1, x2, N);
    EXPECT_THAT(ret2, ElementsAreArray({DoubleEq(0.0),
                    DoubleEq(0.1),
                    DoubleEq(0.2),
                    DoubleEq(0.3),
                    DoubleEq(0.4),
                    DoubleEq(0.5)}));
}

TEST(TestLinspace, ReturnSTDVector)
{
    double x1 = 0.0;
    double x2 = 0.5;
    double h = 0.1;
    size_t N = static_cast<size_t>((x2 - x1)/h) + 1;
    std::vector<double> ret = meshgen::linspace(x1, x2, N);
    EXPECT_THAT(ret, ElementsAreArray({DoubleEq(0.0),
                    DoubleEq(0.1),
                    DoubleEq(0.2),
                    DoubleEq(0.3),
                    DoubleEq(0.4),
                    DoubleEq(0.5)}));
}

TEST(TestMeshgrid, Meshgrid2D)
{
    std::vector<double> x(1);
    x[0] = 0.0;
    std::vector<double> y(2);
    y[0] = 0.1;
    y[1] = 0.2;
    meshgen::mesh_grid<double, 0, 2> X;
    meshgen::mesh_grid<double, 1, 2> Y;

    std::tie(X, Y) = meshgen::meshgrid(x, y);
    EXPECT_DOUBLE_EQ(X(0, 0), 0.0);
    EXPECT_DOUBLE_EQ(X(0, 1), 0.0);
    EXPECT_DOUBLE_EQ(Y(0, 0), 0.1);
    EXPECT_DOUBLE_EQ(Y(0, 1), 0.2);

    std::tie(X, Y) = meshgen::meshgrid(x.begin(), x.end(), y.begin(), y.end());
    EXPECT_DOUBLE_EQ(X(0, 0), 0.0);
    EXPECT_DOUBLE_EQ(X(0, 1), 0.0);
    EXPECT_DOUBLE_EQ(Y(0, 0), 0.1);
    EXPECT_DOUBLE_EQ(Y(0, 1), 0.2);

    std::tie(X, Y) = meshgen::meshgrid(&x[0], &x[0] + x.size(), &y[0], &y[0] + y.size());
    EXPECT_DOUBLE_EQ(X(0, 0), 0.0);
    EXPECT_DOUBLE_EQ(X(0, 1), 0.0);
    EXPECT_DOUBLE_EQ(Y(0, 0), 0.1);
    EXPECT_DOUBLE_EQ(Y(0, 1), 0.2);
}

TEST(TestMeshgrid, Meshgrid3D)
{
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
    EXPECT_DOUBLE_EQ(X(0, 0, 0), 0.0);
    EXPECT_DOUBLE_EQ(X(0, 1, 0), 0.0);
    EXPECT_DOUBLE_EQ(X(0, 0, 1), 0.0);
    EXPECT_DOUBLE_EQ(X(0, 1, 1), 0.0);
    EXPECT_DOUBLE_EQ(Y(0, 0, 0), 0.1);
    EXPECT_DOUBLE_EQ(Y(0, 1, 0), 0.2);
    EXPECT_DOUBLE_EQ(Y(0, 0, 1), 0.1);
    EXPECT_DOUBLE_EQ(Y(0, 1, 1), 0.2);
    EXPECT_DOUBLE_EQ(Z(0, 0, 0), 0.3);
    EXPECT_DOUBLE_EQ(Z(0, 1, 0), 0.3);
    EXPECT_DOUBLE_EQ(Z(0, 0, 1), 0.4);
    EXPECT_DOUBLE_EQ(Z(0, 1, 1), 0.4);

    std::tie(X, Y, Z) = meshgen::meshgrid(x.begin(), x.end(),
                                 y.begin(), y.end(),
                                 z.begin(), z.end());
    EXPECT_DOUBLE_EQ(X(0, 0, 0), 0.0);
    EXPECT_DOUBLE_EQ(X(0, 1, 0), 0.0);
    EXPECT_DOUBLE_EQ(X(0, 0, 1), 0.0);
    EXPECT_DOUBLE_EQ(X(0, 1, 1), 0.0);
    EXPECT_DOUBLE_EQ(Y(0, 0, 0), 0.1);
    EXPECT_DOUBLE_EQ(Y(0, 1, 0), 0.2);
    EXPECT_DOUBLE_EQ(Y(0, 0, 1), 0.1);
    EXPECT_DOUBLE_EQ(Y(0, 1, 1), 0.2);
    EXPECT_DOUBLE_EQ(Z(0, 0, 0), 0.3);
    EXPECT_DOUBLE_EQ(Z(0, 1, 0), 0.3);
    EXPECT_DOUBLE_EQ(Z(0, 0, 1), 0.4);
    EXPECT_DOUBLE_EQ(Z(0, 1, 1), 0.4);

    std::tie(X, Y, Z) = meshgen::meshgrid(&x[0], &x[0] + x.size(),
                                 &y[0], &y[0] + y.size(),
                                 &z[0], &z[0] + z.size());
    EXPECT_DOUBLE_EQ(X(0, 0, 0), 0.0);
    EXPECT_DOUBLE_EQ(X(0, 1, 0), 0.0);
    EXPECT_DOUBLE_EQ(X(0, 0, 1), 0.0);
    EXPECT_DOUBLE_EQ(X(0, 1, 1), 0.0);
    EXPECT_DOUBLE_EQ(Y(0, 0, 0), 0.1);
    EXPECT_DOUBLE_EQ(Y(0, 1, 0), 0.2);
    EXPECT_DOUBLE_EQ(Y(0, 0, 1), 0.1);
    EXPECT_DOUBLE_EQ(Y(0, 1, 1), 0.2);
    EXPECT_DOUBLE_EQ(Z(0, 0, 0), 0.3);
    EXPECT_DOUBLE_EQ(Z(0, 1, 0), 0.3);
    EXPECT_DOUBLE_EQ(Z(0, 0, 1), 0.4);
    EXPECT_DOUBLE_EQ(Z(0, 1, 1), 0.4);

}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
