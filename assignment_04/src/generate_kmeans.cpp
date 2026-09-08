#include <iostream>
#include <fstream>
#include <random>
#include <iomanip>

void generateKMeansTest(int N, int D, int K, const std::string& filename) {
    std::ofstream out(filename);
    out << N << " " << D << " " << K << "\n";
    
    std::mt19937 rng(42); 
    std::uniform_real_distribution<double> dist(0.0, 100.0); // Points between 0 and 100

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < D; ++j) {
            out << std::fixed << std::setprecision(4) << dist(rng) << (j == D-1 ? "" : " ");
        }
        out << "\n";
    }

    
    out << "MAX_ITERATIONS 300\n";
    out << "TOLERANCE 0.0001\n";
    
    out.close();
    std::cout << "Generated " << filename << " (N=" << N << ", D=" << D << ", K=" << K << ")\n";
}

int main() {
    generateKMeansTest(100, 2, 3, "tests/km_01.txt");
    generateKMeansTest(1000, 2, 5, "tests/km_02.txt");
    generateKMeansTest(10000, 5, 8, "tests/km_03.txt");
    generateKMeansTest(100000, 5, 10, "tests/km_04.txt");
    
    std::cout << "All K-Means tests successfully generated!\n";
    return 0;
}