#include <iostream>
#include <cmath>
#include <fstream>

double rk4(double(*f)(double, double), double dt, double t, double y)
{
    double k1, k2, k3, k4;
    k1 = dt * f(t, y);
    k2 = dt * f(t + dt / 2, y + k1 / 2);
    k3 = dt * f(t + dt / 2, y + k2 / 2);
    k4 = dt * f(t + dt, y + k3);
    return y + (k1 + 2 * k2 + 2 * k3 + k4) / 6;
}

double diffEq(double t, double y)
{
    double dy;

    dy = t - y;

    return dy;
}

int main(void)
{
    double *y, t;
    double t0 = 0, dt = .1, tf = 10;
    int i;
    int i1;

    i1 = int (1 + (tf - t0) / dt);
    y = (double *) malloc(sizeof(double) * i1);
    for(y[0] = 1, i = 1; i < i1; i++)
        y[i] = rk4(diffEq, dt, t0 + dt * (i - 1), y[i - 1]);

    std::ofstream fileID;
    fileID.open("sol.csv");
    for(i = 0; i < i1; i ++)
    {
        t = t0 + dt * i;
        fileID << t;
        fileID << ",";
        fileID << y[i];
        fileID << "\n";
    }
    fileID.close();

    return 0;
}

