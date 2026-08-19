#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void generate_gradient_descent_test(string filename, int degree, string coeffs, double x0, double lr, double tol, int max_iter){
    string full_path = "tests/" + filename;
    ofstream outfile(full_path);
    if (!outfile.is_open()){
        cerr << "Error: Could not create file at " << full_path << "\n";
        return;
    }

    outfile << "DEGREE " << degree << "\n"
            << "COEFFICIENTS " << coeffs << "\n"
            << "INITIAL_X " << x0 << "\n"
            << "LEARNING_RATE " << lr << "\n"
            << "TOLERANCE " << tol << "\n"
            << "MAX_ITERATIONS " << max_iter << "\n";
            
    cout << "Generated " << full_path << " successfully.\n";
}

int main(){
    // gd_01: Degree 2, f(x) = x^2 - 6x + 9
    generate_gradient_descent_test("gd_01.txt", 2, "9 -6 1", 0, 0.10, 1e-6, 5000);

    // gd_02: Degree 4, f(x) = x^4 + 2x^2
    generate_gradient_descent_test("gd_02.txt", 4, "0 0 2 0 1", 2, 0.02, 1e-6, 10000);

    // gd_03: Degree 6, f(x) = 0.1x^6 + 0.5x^4 + x^2
    generate_gradient_descent_test("gd_03.txt", 6, "0 0 1 0 0.5 0 0.1", 2, 0.02, 1e-6, 20000);

    // gd_04: Degree 8, f(x) = 0.01x^8 + 0.05x^6 + 0.2x^4 + x^2
    generate_gradient_descent_test("gd_04.txt", 8, "0 0 1 0 0.2 0 0.05 0 0.01", 2, 0.01, 1e-8, 50000);

    // gd_05: Degree 10, f(x) = 0.002x^10 + 0.01x^8 + 0.05x^6 + 0.2x^4 + x^2
    generate_gradient_descent_test("gd_05.txt", 10, "0 0 1 0 0.2 0 0.05 0 0.01 0 0.002", 2, 0.005, 1e-10, 100000);
}