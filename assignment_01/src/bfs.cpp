#include "../headers/csr_graph_creation.h"
#include <iostream>
#include <vector>
#include <queue>
#include <chrono>
#include <fstream>
#include <string>
#include <climits>

using namespace std;

// helper function for BFS
void BFS(int source, CSRGraph& graph, vector<int>& distance, vector<int>& traversal) {
    queue<int> q;
    q.push(source);
    distance[source] = 0;
    traversal.push_back(source);
    
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        int start_edge = graph.row_ptr[node];
        int end_edge = graph.row_ptr[node+1];
        for (int i = start_edge; i < end_edge; i++) {
            int neighbor = graph.col_idx[i];
            // if neighbor is not visited yet, update its distance and add it to queue
            if (distance[neighbor] == INT_MAX) {
                distance[neighbor] = distance[node] + 1;
                traversal.push_back(neighbor);
                q.push(neighbor);
            }
        }
    }
}

// function to run BFS on CSR graph
void run_BFS(CSRGraph& graph, int V, int source) {
    double total_time = 0;
    int runs = (V <= 100)? 100 : 1; // assuming no. of nodes <= 100 are considered 'fast inputs', let's take the average execution time over 100 runs
    vector<int> distance, traversal;

    for(int r=0;r<runs;r++){
        distance.assign(V, INT_MAX); // initialize distances to infinity, for every run
        traversal.clear(); // reset traversal vector for every run

        auto start_time = chrono::high_resolution_clock::now(); // Start timer for BFS
        BFS(source, graph, distance, traversal);
        auto end_time = chrono::high_resolution_clock::now(); // End timer for BFS

        total_time += chrono::duration<double, milli>(end_time - start_time).count();
    }
    
    // cout << "Algorithm: BFS\nSource: " << source << "\nTraversal: ";
    // for (int node : traversal){
    //     cout << node << " ";
    // }
    // cout << "\nDistances:\n";
    // for (int i=0;i<V;i++){
    //     if(distance[i]==INT_MAX){ 
    //         cout << i << " INF\n";
    //     }
    //     else{
    //         cout << i << " " << distance[i] << "\n";
    //     }
    // }
    cout << "Execution time: " << total_time/runs << " ms\n\n";
}

void run_BFS_test(){
    int V, E, source; // number of vertices and edges, and source node
    string filename; // input filename
    vector<vector<int>> adj; // adjacency list (unweighted graph)

    cout << "Enter input filename: ";
    cin >> filename;
    
    // read graph from file and populate adjacency list
    if(!read_unweighted_graph(filename, adj, V, E, source)){
        cout << "Error reading graph from file: " << filename << endl;
        return;
    }

    CSRGraph csr = convert_unweighted_graph_to_CSR(adj); // convert adjacency list to CSR format
    run_BFS(csr, V, source);
}