#include <iostream>
#include <fstream>
#include <random>
#include <iomanip>

using namespace std;

void generateKMeansTest(int N, int D, int K, string filename) {
    ofstream out(filename);
    out << N << " " << D << " " << K << "\n";
    
    mt19937 rng(42); 
    uniform_real_distribution<double> dist(0.0, 100.0); // Points between 0 and 100

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < D; j++) {
            out << fixed << setprecision(4) << dist(rng) << (j == D-1 ? "" : " ");
        }
        out << "\n";
    }
    
    int max_iterations = 300;
    double tolerance = 0.0001;

    out << "MAX_ITERATIONS " << max_iterations << "\n";
    out << "TOLERANCE " << tolerance << "\n";
    
    out.close();
    cout << "Generated " << filename << " (N=" << N << ", D=" << D << ", K=" << K << ")\n";
}

int main() {
    generateKMeansTest(100, 2, 3, "tests/km_01.txt");
    generateKMeansTest(1000, 2, 5, "tests/km_02.txt");
    generateKMeansTest(10000, 5, 8, "tests/km_03.txt");
    generateKMeansTest(100000, 5, 10, "tests/km_04.txt");
    
    cout << "All K-Means tests successfully generated!\n";
    return 0;
}