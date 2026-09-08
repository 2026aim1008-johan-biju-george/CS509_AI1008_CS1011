#ifndef GRADIENT_DESCENT_H
#define GRADIENT_DESCENT_H

using namespace std;

struct GDResult{
    int degree;
    double final_x;
    double final_fx;
    int iterations;
    bool converged;
    long long execution_time_ms;
};

void run_gradient_descent_test();

#endif