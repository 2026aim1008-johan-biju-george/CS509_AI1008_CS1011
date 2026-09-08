#include "../headers/kmeans.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <chrono>
#include <iomanip>


double squaredDistance(const std::vector<double>& a, const std::vector<double>& b) {
    double sum = 0.0;
    for (size_t i = 0; i < a.size(); ++i) {
        sum += (a[i] - b[i]) * (a[i] - b[i]);
    }
    return sum;
}


double euclideanDistance(const std::vector<double>& a, const std::vector<double>& b) {
    return std::sqrt(squaredDistance(a, b));
}

void runKMeansTask(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Error: Missing or invalid input file.\n";
        return;
    }

    int N, D, K;
    if (!(file >> N >> D >> K)) return;

    
    if (N <= 0 || D <= 0 || K <= 0 || K > N) {
        std::cerr << "Error: Invalid N, D, or K.\n";
        return;
    }

    std::vector<std::vector<double>> points(N, std::vector<double>(D));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < D; ++j) {
            file >> points[i][j];
        }
    }

    std::string label;
    int max_iter = 0;
    double tolerance = 0.0;
    
    while (file >> label) {
        if (label == "MAX_ITERATIONS") file >> max_iter;
        else if (label == "TOLERANCE") file >> tolerance;
    }
    file.close();

    if (max_iter <= 0 || tolerance <= 0) {
        std::cerr << "Error: Invalid tolerance or max_iterations.\n";
        return;
    }

    std::vector<int> assignments(N, -1);
    std::vector<std::vector<double>> centroids(K, std::vector<double>(D));
    
    
    auto start = std::chrono::high_resolution_clock::now();

    
    for (int i = 0; i < K; ++i) {
        centroids[i] = points[i];
    }

    int iterations = 0;
    bool converged = false;
    
    while (iterations < max_iter) {
        bool assignment_changed = false;

        
        for (int i = 0; i < N; ++i) {
            double min_dist = -1.0;
            int best_cluster = -1;
            for (int k = 0; k < K; ++k) {
                double dist = squaredDistance(points[i], centroids[k]);
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

        
        std::vector<std::vector<double>> new_centroids(K, std::vector<double>(D, 0.0));
        std::vector<int> cluster_counts(K, 0);

        for (int i = 0; i < N; ++i) {
            int cluster = assignments[i];
            cluster_counts[cluster]++;
            for (int j = 0; j < D; ++j) {
                new_centroids[cluster][j] += points[i][j];
            }
        }

        double max_shift = 0.0;
        for (int k = 0; k < K; ++k) {
            if (cluster_counts[k] > 0) {
                for (int j = 0; j < D; ++j) {
                    new_centroids[k][j] /= cluster_counts[k];
                }
                double shift = euclideanDistance(centroids[k], new_centroids[k]);
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

    
    double wcss = 0.0;
    for (int i = 0; i < N; ++i) {
        wcss += squaredDistance(points[i], centroids[assignments[i]]);
    }


    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;


    std::cout << "Algorithm: K-Means Clustering\n";
    std::cout << "K: " << K << "\n";
    
    if (N <= 100) {
        std::cout << "Point assignments:\n";
        for (int i = 0; i < N; ++i) {
            std::cout << i << " " << assignments[i] << "\n";
        }
    } else {
        std::cout << "Point assignments: (Omitted from output for large datasets N > 100)\n";
    }

    std::cout << "Final centroids:\n";
    for (int k = 0; k < K; ++k) {
        std::cout << k << ": ";
        for (int j = 0; j < D; ++j) {
            std::cout << std::fixed << std::setprecision(6) << centroids[k][j] << " ";
        }
        std::cout << "\n";
    }

    std::cout << "WCSS: " << std::fixed << std::setprecision(6) << wcss << "\n";
    std::cout << "Iterations: " << iterations << "\n";
    std::cout << "Converged: " << (converged ? "true" : "false") << "\n";
    std::cout << "Execution time: " << duration.count() << " ms\n";
}