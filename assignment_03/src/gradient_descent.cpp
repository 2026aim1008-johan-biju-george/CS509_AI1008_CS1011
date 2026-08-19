#include "../headers/gradient_descent.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <chrono>

// Evaluate polynomial: f(x) = c0 + c1*x + ... + cd*x^d
double evaluate_poly(vector<double>& c, double x){
    double val = 0.0;
    double x_power = 1.0;
    for(int i=0;i<c.size();i++){
        val += c[i] * x_power;
        x_power *= x;
    }
    return val;
}

// Evaluate derivative: f'(x) = c1 + 2*c2*x + ... + d*cd*x^(d-1)
double evaluate_derivative(vector<double>& c, double x){
    double val = 0.0;
    double x_power = 1.0;
    for (int i=1;i<c.size();i++){
        val += i * c[i] * x_power;
        x_power *= x;
    }
    return val;
}

GDResult gradient_descent(int degree, vector<double>& coefficients, double initial_x, double learning_rate, double tolerance, int max_iterations){
    // Timing start
    auto start_time = std::chrono::high_resolution_clock::now();

    double x = initial_x;
    int iter = 0;
    bool converged = false;

    for(iter=0;iter<max_iterations;iter++){
        double deriv = evaluate_derivative(coefficients, x);
    
        // Stop when |f'(x)| <= tolerance
        if (abs(deriv) <= tolerance){
            converged = true;
            break;
        }
        
        // Update x using x_new = x - alpha*f'(x)
        x = x - learning_rate * deriv;
    }
    
    // Timing end
    auto end_time = chrono::high_resolution_clock::now();

    GDResult res;
    res.degree = degree;
    res.final_x = x;
    res.final_fx = evaluate_poly(coefficients, x);
    res.iterations = iter + (converged ? 1 : 0);
    res.converged = converged;
    res.execution_time_ms = chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count();
    
    return res;
}

void run_gradient_descent_test(){
    string filename;
    cout << "Enter input file path: ";
    cin >> filename;
    
    ifstream infile(filename);
    if (!infile.is_open()){
        cerr << "Error: Could not open input file " << filename << "\n";
        return;
    }

    string temp;
    int degree;
    infile >> temp >> degree;
    
    infile >> temp;
    vector<double> coeffs(degree + 1);
    for (int i=0;i<=degree;i++){
        infile >> coeffs[i];
    }

    double x0, lr, tol;
    int max_iter;
    infile >> temp >> x0;       // INITIAL_X x0
    infile >> temp>> lr;       // LEARNING_RATE alpha
    infile >> temp >> tol;      // TOLERANCE epsilon
    infile >> temp>> max_iter; // MAX_ITERATIONS 

    GDResult res = gradient_descent(degree, coeffs, x0, lr, tol, max_iter);

    // Gradient Descent Output
    cout << "\nAlgorithm: Gradient Descent\n"
            << "Degree: " << res.degree << "\n"
            << "Final x: approximately " << res.final_x << "\n"
            << "Final f(x): approximately " << res.final_fx << "\n"
            << "Iterations: " << res.iterations << "\n"
            << "Converged: " << (res.converged ? "true" : "false") << "\n"
            << "Execution time: " << res.execution_time_ms << " ms\n";
}