#include "../headers/kmeans.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <chrono>
#include <iomanip>

using namespace std;

double squared_distance(vector<double>& a, vector<double>& b) {
    double sum = 0.0;
    for (size_t i = 0; i < a.size(); i++) {
        sum += (a[i] - b[i]) * (a[i] - b[i]);
    }
    return sum;
}


double euclidean_distance(vector<double>& a, vector<double>& b) {
    return sqrt(squared_distance(a, b));
}

void run_k_means(vector<vector<double>>& points, int N, int D, int K, int max_iter, double tolerance, vector<int>& assignments, 
                vector<vector<double>>& centroids, double& wcss, int& iterations, bool& converged) {
    for (int i = 0; i < K; i++) {
        centroids[i] = points[i];
    }
    
    while (iterations < max_iter) {
        bool assignment_changed = false;

        for (int i = 0; i < N; i++) {
            double min_dist = -1.0;
            int best_cluster = -1;
            for (int k = 0; k < K; k++) {
                double dist = squared_distance(points[i], centroids[k]);
                if (best_cluster == -1 || dist < min_dist) {
                    min_dist = dist;
                    best_cluster = k;
                }
            }
            if (assignments[i] != best_cluster) {
                assignments[i] = best_cluster;
                assignment_changed = true;
            }
        }

        vector<vector<double>> new_centroids(K, vector<double>(D, 0.0));
        vector<int> cluster_counts(K, 0);

        for (int i = 0; i < N; i++) {
            int cluster = assignments[i];
            cluster_counts[cluster]++;
            for (int j = 0; j < D; j++) {
                new_centroids[cluster][j] += points[i][j];
            }
        }

        double max_shift = 0.0;
        for (int k = 0; k < K; k++) {
            if (cluster_counts[k] > 0) {
                for (int j = 0; j < D; j++) {
                    new_centroids[k][j] /= cluster_counts[k];
                }
                double shift = euclidean_distance(centroids[k], new_centroids[k]);
                if (shift > max_shift) {
                    max_shift = shift;
                }
                centroids[k] = new_centroids[k];
            } 
           
        }

        iterations++;

        if (!assignment_changed || max_shift <= tolerance) {
            converged = true;
            break;
        }
    }

    for (int i = 0; i < N; i++) {
        wcss += squared_distance(points[i], centroids[assignments[i]]);
    }
}

void run_k_means_test(string& filepath) {
    ifstream file(filepath);
    if (!file.is_open()) {
        cerr << "Error: Missing or invalid input file.\n";
        return;
    }

    int N, D, K;
    if (!(file >> N >> D >> K)) return;
    
    if (N <= 0 || D <= 0 || K <= 0 || K > N) {
        cerr << "Error: Invalid N, D, or K.\n";
        return;
    }

    vector<vector<double>> points(N, vector<double>(D));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < D; j++) {
            file >> points[i][j];
        }
    }

    string label;
    int max_iter = 0;
    double tolerance = 0.0;
    double wcss = 0.0;
    int iterations = 0;
    bool converged = false;
    
    while (file >> label) {
        if (label == "MAX_ITERATIONS") file >> max_iter;
        else if (label == "TOLERANCE") file >> tolerance;
    }
    file.close();

    if (max_iter <= 0 || tolerance <= 0) {
        cerr << "Error: Invalid tolerance or max_iterations.\n";
        return;
    }

    vector<int> assignments(N, -1);
    vector<vector<double>> centroids(K, vector<double>(D));
    
    auto start = chrono::high_resolution_clock::now();
    run_k_means(points, N, D, K, max_iter, tolerance, assignments, centroids, wcss, iterations, converged);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start;

    cout << "Algorithm: K-Means Clustering\n";
    cout << "K: " << K << "\n";
    
    if (N <= 100) {
        cout << "Point assignments:\n";
        for (int i = 0; i < N; i++) {
            cout << i << " " << assignments[i] << "\n";
        }
    } else {
        cout << "Point assignments: (Omitted from output for large datasets N > 100)\n";
    }

    cout << "Final centroids:\n";
    for (int k = 0; k < K; k++) {
        cout << k << ": ";
        for (int j = 0; j < D; j++) {
            cout << fixed << setprecision(6) << centroids[k][j] << " ";
        }
        cout << "\n";
    }

    cout << "WCSS: " << fixed << setprecision(6) << wcss << "\n";
    cout << "Iterations: " << iterations << "\n";
    cout << "Converged: " << (converged ? "true" : "false") << "\n";
    cout << "Execution time: " << duration.count() << " ms\n";
}