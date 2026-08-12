#include "../headers/algorithms.hpp"
#include "../headers/graph.hpp"
#include <iostream>
#include <queue>
#include <chrono>

using namespace std;

void runConnectedComponents(const string& filename) {
    CSRGraph graph = loadCSR(filename);

    // Start time
    auto start_time = chrono::high_resolution_clock::now();

    vector<int> component_id(graph.V, -1);
    int current_comp_id = 0;

    for (int i = 0; i < graph.V; ++i) {
        if (component_id[i] == -1) {
            queue<int> q;
            q.push(i);
            component_id[i] = current_comp_id;

            while (!q.empty()) {
                int u = q.front();
                q.pop();

                for (int idx = graph.row_ptr[u]; idx < graph.row_ptr[u + 1]; ++idx) {
                    int v = graph.col_idx[idx];
                    if (component_id[v] == -1) {
                        component_id[v] = current_comp_id;
                        q.push(v);
                    }
                }
            }
            current_comp_id++;
        }
    }

    // Stop time
    auto end_time = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> elapsed = end_time - start_time;

    cout << "Algorithm: Connected Components\n";
    cout << "Number of components: " << current_comp_id << "\n";
    cout << "Vertex Component\n";
    for (int i = 0; i < graph.V; ++i) {
        cout << i << " " << component_id[i] << "\n";
    }
    cout << "Execution time: " << elapsed.count() << " ms\n";
}