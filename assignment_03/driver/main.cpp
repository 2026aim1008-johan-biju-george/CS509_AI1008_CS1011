#include "../headers/gradient_decent.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

int main() 
{
    srand(time(0));
    int choice;
    string filename;

    do 
    {
        cout << "Assignment 3 (Buddy Tasks - Gradient Descent)\n";
        cout << "1. Run Gradient Descent\n";
        cout << "0. Exit\n";
        
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) 
        {
            case 1: 
            {
                cout << "Enter input file path: ";
                cin >> filename;
                
                ifstream infile(filename);
                if (!infile.is_open()) 
                {
                    cerr << "Error: Could not open input file " << filename << "\n";
                    break;
                }

                string temp;
                int degree;
                infile >> temp >> degree;
                
                infile >> temp;
                vector<double> coeffs(degree + 1);
                for (int i = 0; i <= degree; ++i) 
                {
                    infile >> coeffs[i];
                }

                double x0, lr, tol;
                int max_iter;
                infile >> temp >> x0;       // INITIAL_X x0
                infile >> temp>> lr;       // LEARNING_RATE alpha
                infile >> temp >> tol;      // TOLERANCE epsilon
                infile >> temp>> max_iter; // MAX_ITERATIONS 

               
                GDResult res = GradientDescent(degree, coeffs, x0, lr, tol, max_iter);

                // Gradient Descent Output
                cout << "\nAlgorithm: Gradient Descent\n"
                     << "Degree: " << res.degree << "\n"
                     << "Final x: approximately " << res.final_x << "\n"
                     << "Final f(x): approximately " << res.final_fx << "\n"
                     << "Iterations: " << res.iterations << "\n"
                     << "Converged: " << (res.converged ? "true" : "false") << "\n"
                     << "Execution time: " << res.execution_time_ms << " ms\n";
                break;
            }

            case 0:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice.\n";
        }
        cout << "\n";
    } while (choice != 0);

    return 0;
}