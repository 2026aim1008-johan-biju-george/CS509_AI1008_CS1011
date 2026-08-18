#include <iostream>
#include <fstream>
#include <string>

void createGDTestFile(const std::string& filename, int degree, const std::string& coeffs, double x0, double lr, double tol, int max_iter) 
{
    
    std::string fullPath = "tests/" + filename;
    
    std::ofstream outfile(fullPath);
    if (!outfile.is_open()) 
    {
        std::cerr << "Error: Could not create file at " << fullPath << "\n";
        return;
    }

    outfile << "DEGREE " << degree << "\n"
            << "COEFFICIENTS " << coeffs << "\n"
            << "INITIAL_X " << x0 << "\n"
            << "LEARNING_RATE " << lr << "\n"
            << "TOLERANCE " << tol << "\n"
            << "MAX_ITERATIONS " << max_iter << "\n";
            
    std::cout << "Generated " << fullPath << " successfully.\n";
}

int main() 
{
    // gd_01: Degree 2, f(x) = x^2 - 6x + 9
    createGDTestFile("gd_01.txt", 2, "9 -6 1", 0, 0.10, 1e-6, 5000);

    // gd_02: Degree 4, f(x) = x^4 + 2x^2
    createGDTestFile("gd_02.txt", 4, "0 0 2 0 1", 2, 0.02, 1e-6, 10000);

    // gd_03: Degree 6, f(x) = 0.1x^6 + 0.5x^4 + x^2
    createGDTestFile("gd_03.txt", 6, "0 0 1 0 0.5 0 0.1", 2, 0.02, 1e-6, 20000);

    // gd_04: Degree 8, f(x) = 0.01x^8 + 0.05x^6 + 0.2x^4 + x^2
    createGDTestFile("gd_04.txt", 8, "0 0 1 0 0.2 0 0.05 0 0.01", 2, 0.01, 1e-8, 50000);

    // gd_05: Degree 10, f(x) = 0.002x^10 + 0.01x^8 + 0.05x^6 + 0.2x^4 + x^2
    createGDTestFile("gd_05.txt", 10, "0 0 1 0 0.2 0 0.05 0 0.01 0 0.002", 2, 0.005, 1e-10, 100000);

    return 0;
}