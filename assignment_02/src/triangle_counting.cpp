#include "../headers/algorithms.hpp"
#include "../headers/graph.hpp"
#include <iostream>
#include <chrono>

using namespace std;

void runTriangleCounting(const string& filename) {
    CSRGraph graph = loadCSR(filename);

    // Start time
    auto start_time = chrono::high_resolution_clock::now();

    long long total_triangles = 0;
    vector<vector<int>> found_triangles;
    bool print_details = (graph.V <= 100); 
    for (int u = 0; u < graph.V; ++u) {
        int start_u = graph.row_ptr[u];
        int end_u = graph.row_ptr[u + 1];

        for (int i = start_u; i < end_u; ++i) {
            int v = graph.col_idx[i];
            if (v <= u) continue;

            int start_v = graph.row_ptr[v];
            int end_v = graph.row_ptr[v + 1];

            // Two-pointer intersection on sorted lists
            int p1 = start_u, p2 = start_v;
            while (p1 < end_u && p2 < end_v) {
                int n_u = graph.col_idx[p1];
                int n_v = graph.col_idx[p2];

                if (n_u == n_v) {
                    if (n_u > v) { 
                        total_triangles++;
                        if (print_details) {
                            found_triangles.push_back({u, v, n_u});
                        }
                    }
                    p1++; p2++;
                } else if (n_u < n_v) {
                    p1++;
                } else {
                    p2++;
                }
            }
        }
    }

    // Stop time
    auto end_time = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> elapsed = end_time - start_time;

    cout << "Algorithm: Triangle Counting\n";
    cout << "Total triangles: " << total_triangles << "\n";
    if (print_details && !found_triangles.empty()) {
        cout << "Triangles found:\n";
        for (const auto& t : found_triangles) {
            cout << "(" << t[0] << ", " << t[1] << ", " << t[2] << ")\n";
        }
    }
    cout << "Execution time: " << elapsed.count() << " ms\n";
}