#include "../headers/fastmap.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

// Generate pairwise Euclidean distance matrix
void generate_fastmap_input(int N, int K) {
    string filename = "tests/fm_" + to_string(N) + ".txt";
    ofstream fout(filename);

    if(!fout) {
        cout << "Cannot create file: " << filename << endl;
        return;
    }

    if(N <= 0 || K <= 0) {
        cout << "Invalid N or K." << endl;
        return;
    }

    // Generate random points in a higher-dimensional space
    vector<vector<double>> points(N, vector<double>(3));

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < 3; j++) {
            // Random value between 0 and 10
            points[i][j] = (double)rand() / RAND_MAX * 10.0;
        }
    }

    // Write N and target dimensions K
    fout << N << " " << K << endl;

    // Generate and write pairwise distance matrix
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            double distance = 0.0;
            for(int d = 0; d < 3; d++) {
                double difference = points[i][d] - points[j][d];
                distance += difference * difference;
            }

            distance = sqrt(distance);
            fout << fixed << setprecision(6) << distance;

            if(j < N - 1) fout << " ";
        }
        fout << endl;
    }
    fout.close();
}

// Generate FastMap test cases
int main() {
    generate_fastmap_input(10, 2);
    generate_fastmap_input(100, 2);
    generate_fastmap_input(1000, 2);
    generate_fastmap_input(10000, 2);
    
    cout << "All FastMap tests successfully generated!\n";
    return 0;
}