#include "../headers/gradient_decent.hpp"
#include <cmath>
#include <chrono>

// Evaluate polynomial: f(x) = c0 + c1*x + ... + cd*x^d
static double evaluatePoly(const std::vector<double>& c, double x) 
{
    double val = 0.0;
    double x_power = 1.0;
    for (size_t i = 0; i < c.size(); ++i) 
    {
        val += c[i] * x_power;
        x_power *= x;
    }
    return val;
}

// Evaluate derivative: f'(x) = c1 + 2*c2*x + ... + d*cd*x^(d-1)
static double evaluateDerivative(const std::vector<double>& c, double x) 
{
    double val = 0.0;
    double x_power = 1.0;
    for (size_t i = 1; i < c.size(); ++i) 
    {
        val += i * c[i] * x_power;
        x_power *= x;
    }
    return val;
}

GDResult GradientDescent(int degree, const std::vector<double>& coefficients, double initial_x, double learning_rate, double tolerance, int max_iterations) 
{
    // Timing start
    auto start_time = std::chrono::high_resolution_clock::now();

    double x = initial_x;
    int iter = 0;
    bool converged = false;

    for (iter = 0; iter < max_iterations; ++iter) 
    {
        double deriv = evaluateDerivative(coefficients, x);
        
        // Stop when |f'(x)| <= tolerance
        if (std::abs(deriv) <= tolerance) 
        {
            converged = true;
            break;
        }
        
        // Update x using x_new = x - alpha*f'(x)
        x = x - learning_rate * deriv;
    }

    auto end_time = std::chrono::high_resolution_clock::now();

    GDResult res;
    res.degree = degree;
    res.final_x = x;
    res.final_fx = evaluatePoly(coefficients, x);
    res.iterations = iter + (converged ? 1 : 0);
    res.converged = converged;
    res.execution_time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
    
    return res;
}