#ifndef GRADIENT_DESCENT_H
#define GRADIENT_DESCENT_H

#include <vector>

struct GDResult 
{
    int degree;
    double final_x;
    double final_fx;
    int iterations;
    bool converged;
    long long execution_time_ms;
};

GDResult GradientDescent(int degree, const std::vector<double>& coefficients, double initial_x, double learning_rate, double tolerance, int max_iterations);

#endif