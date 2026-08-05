#include "../headers/csr_graph_creation.h"
#include <iostream>
#include <vector>
#include <queue>
#include <chrono>
#include <fstream>
#include <string>
#include <climits>

using namespace std;

// Dijkstra's Algorithm for SSSP
void SSSP(int source, CSRGraph& graph, int V, vector<int>& distance){
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq; // min-heap priority queue
    distance[source] = 0; // distance from source to itself is zero
    pq.push({0, source}); // push source node with distance zero

    while(!pq.empty()){
        int dist = pq.top().first;
        int node = pq.top().second;
        pq.pop();

        if(dist > distance[node]) continue; // skip if we have already found a better path
        int start_edge = graph.row_ptr[node];
        int end_edge = graph.row_ptr[node+1];
        for(int i = start_edge; i < end_edge; i++){
            int neighbor = graph.col_idx[i];
            int weight = graph.values[i]; // edge weight
            // update distance if shorter path is found
            if(distance[node] + weight < distance[neighbor]){
                distance[neighbor] = distance[node] + weight;
                pq.push({distance[neighbor], neighbor});
            }
        }
    }
}

// function to run SSSP on CSR graph
void run_SSSP(CSRGraph& graph, int V, int source) {
    vector<int> distance(V, INT_MAX); // initialize distances to infinity
    
    auto start_time = chrono::high_resolution_clock::now(); // Start timer for SSSP
    SSSP(source, graph, V, distance);
    auto end_time = chrono::high_resolution_clock::now(); // End timer for SSSP
    
    auto duration = chrono::duration<double, milli>(end_time - start_time).count();
    cout << "Algorithm: SSSP\nSource: " << source << "\nVertex Distance\n";
    for(int i=0;i<V;i++){
        if(distance[i]==INT_MAX){ 
            cout << i << "      " << "INF\n";
        }
        else{
            cout << i << "      " << distance[i] << "\n";
        }
    }
    cout << "Execution time: " << duration << " ms\n\n";
}

void run_SSSP_test(){
    int V, E, source; // number of vertices and edges, and source node
    string filename; // input filename
    vector<vector<pair<int, int>>> adj; // adjacency list (weighted graph)

    cout << "Enter input filename: ";
    cin >> filename;
    
    // read graph from file and populate adjacency list
    if(!read_weighted_graph(filename, adj, V, E, source)){
        cout << "Error reading graph from file: " << filename << endl;
        return;
    }

    CSRGraph csr = convert_weighted_graph_to_CSR(adj); // convert adjacency list to CSR format
    run_SSSP(csr, V, source);
}