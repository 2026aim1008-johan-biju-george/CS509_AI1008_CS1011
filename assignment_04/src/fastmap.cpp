#include "../headers/fastmap.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <chrono>
#include <iomanip>
#include <algorithm>

using namespace std;

// Find the farthest object from a given object
int find_farthest(vector<vector<double>>& distances, int object, vector<double>& residual_distances) {
    int farthest = object;
    double max_distance = -1.0;

    int N = distances.size();

    for(int i = 0; i < N; i++) {
        double distance = residual_distances[i];

        if(distance > max_distance) {
            max_distance = distance;
            farthest = i;
        }
    }
    return farthest;
}


// Calculate residual distance after projecting onto one dimension
double calculate_residual_distance(double distance, double coordinate_i, double coordinate_j) {
    double residual_squared = distance * distance - (coordinate_i - coordinate_j) * (coordinate_i - coordinate_j);

    // Avoid small negative values caused by floating-point errors
    if(residual_squared < 0.0)
        residual_squared = 0.0;

    return sqrt(residual_squared);
}


// FastMap algorithm
void run_fastmap(vector<vector<double>>& distances, int N, int K, vector<vector<double>>& coordinates, vector<pair<int, int>>& pivots) {
    coordinates.assign(N, vector<double>(K, 0.0));
    pivots.clear();

    // Residual distances
    vector<vector<double>> residual(N, vector<double>(N, 0.0));

    // Initially residual distances are original distances
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            residual[i][j] = distances[i][j];
        }
    }

    // Process each target dimension
    for(int dimension = 0; dimension < K; dimension++) {

        // Choose first pivot
        int pivot_a = 0;

        // Find farthest object from pivot_a
        int pivot_b = 0;
        double max_distance = -1.0;

        for(int i = 0; i < N; i++) {
            if(residual[pivot_a][i] > max_distance) {
                max_distance = residual[pivot_a][i];
                pivot_b = i;
            }
        }

        // Find second pivot
        pivot_a = pivot_b;
        pivot_b = 0;
        max_distance = -1.0;

        for(int i = 0; i < N; i++) {
            if(residual[pivot_a][i] > max_distance) {
                max_distance = residual[pivot_a][i];
                pivot_b = i;
            }
        }

        // Store pivot pair
        pivots.push_back({pivot_a, pivot_b});


        // Distance between pivots
        double pivot_distance = residual[pivot_a][pivot_b];

        // If pivots are identical, no further meaningful dimension can be created
        if(pivot_distance <= 1e-12) {
            for(int i = 0; i < N; i++)
                coordinates[i][dimension] = 0.0;
            continue;
        }


        // Calculate coordinates
        for(int i = 0; i < N; i++) {
            double dai = residual[pivot_a][i];
            double dbi = residual[pivot_b][i];
            double dab = pivot_distance;

            double coordinate = (dai * dai + dab * dab - dbi * dbi) / (2.0 * dab);
            coordinates[i][dimension] = coordinate;
        }

        // Update residual distance matrix
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < N; j++) {
                residual[i][j] = calculate_residual_distance(residual[i][j], coordinates[i][dimension], coordinates[j][dimension]);
            }
        }
    }
}


// Function to run FastMap test
void run_fastmap_test(string& filepath) {
    ifstream file(filepath);

    if(!file.is_open()) {
        cerr << "Error: Missing or invalid input file." << endl;
        return;
    }

    // Read N and K
    int N, K;

    if(!(file >> N >> K) || N <= 0 || K <= 0 || K > N) {
        cerr << "Invalid N or K." << endl;
        return;
    }

    // Read pairwise distance matrix
    vector<vector<double>> distances(N, vector<double>(N));

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            if(!(file >> distances[i][j])) {
                cerr << "Error: Invalid distance matrix." << endl;
                return;
            }
        }
    }
    file.close();

    // Allocate output
    vector<vector<double>> coordinates;
    vector<pair<int, int>> pivots;

    // Run FastMap
    auto start = chrono::high_resolution_clock::now();
    run_fastmap(distances, N, K, coordinates, pivots);
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double, milli> duration = end - start;

    cout << "Algorithm: FastMap\n";
    cout << "Target dimensions: " << K << "\n";
    cout << "Pivots per dimension:\n";
    for(int dimension = 0; dimension < K; dimension++) {
        cout << "Dim " << dimension + 1 << ": " << pivots[dimension].first << " " << pivots[dimension].second << "\n";
    }

    // Print coordinates for small datasets
    if(N <= 100) {
        cout << "Object coordinates:\n";
        for(int i = 0; i < N; i++) {
            cout << i << ": ";
            for(int dimension = 0; dimension < K; dimension++) {
                cout << fixed << setprecision(6) << coordinates[i][dimension];
                if(dimension < K - 1) cout << " ";
            }
            cout << "\n";
        }
    }

    cout << "Execution time: " << duration.count() << " ms\n";
}