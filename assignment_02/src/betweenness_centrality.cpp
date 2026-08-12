#include "../headers/algorithms.hpp"
#include "../headers/graph.hpp"

#include <iostream>
#include <queue>
#include <vector>
#include <chrono>
#include <iomanip>

using namespace std;

void runBetweennessCentrality(const string& filename){
    CSRGraph graph = loadCSR(filename);

    auto start = chrono::high_resolution_clock::now();

    int V = graph.V;
    vector<double> BC(V, 0.0);

    // Run BFS from every vertex
    for(int source = 0; source < V; source++){
        vector<int> distance(V, -1);
        vector<int> paths(V, 0);
        vector<int> order;
        vector<vector<int>> parent(V);

        queue<int> q;

        // Start BFS from source
        distance[source] = 0;
        paths[source] = 1;
        q.push(source);

        while (!q.empty()){
            int u = q.front();
            q.pop();

            order.push_back(u);

            // Visit all neighbours of u
            for (int i = graph.row_ptr[u];i < graph.row_ptr[u + 1];i++){
                int v = graph.col_idx[i];

                // First visit to v
                if (distance[v] == -1){
                    distance[v] = distance[u] + 1;
                    q.push(v);
                }

                // u is part of a shortest path to v
                if (distance[v] == distance[u] + 1){
                    paths[v] += paths[u];
                    parent[v].push_back(u);
                }
            }
        }

        // Calculate dependency values
        vector<double> dependency(V, 0.0);

        for(int i=order.size()-1;i>=0;i--){
            int v = order[i];
            for (int u : parent[v]){
                dependency[u] += ((double)paths[u] / paths[v]) * (1.0 + dependency[v]);
            }

            if (v != source)
                BC[v] += dependency[v];
        }
    }

    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double, milli> time = end - start;

    // Print results
    cout << "Algorithm: Betweenness Centrality\n";
    if(V < 50000){
    cout << "Vertex Centrality\n";

    for (int i=0;i<V;i++){
        cout << i << " " << fixed << setprecision(2) << BC[i] << "\n";
    }
}

    cout << "Execution time: " << time.count() << " ms\n";
}