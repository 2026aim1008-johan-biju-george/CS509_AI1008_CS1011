#include "../headers/csr_graph_creation.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <string>
#include <climits>

using namespace std;

// function to read weighted graph from file into adjacency list
bool read_weighted_graph(string& filename, vector<vector<pair<int, int>>>& adj, int& V, int& E){
    ifstream fin(filename); // input file pointer
    if(!fin){
        cout << "Cannot open file: " << filename << endl;
        return false;
    }
    
    fin >> V >> E; // read input of number of vertices and edges
    adj.assign(V, vector<pair<int, int>>()); // initialize adjacency list
    // read the adjacency list from file, and populate the adjacency list vector
    for(int i=0;i<V;i++){
        int node, degree;
        fin >> node >> degree;
        for(int j=0;j<degree;j++){
            int neighbor, weight;
            fin >> neighbor >> weight;
            adj[node].push_back({neighbor, weight});
        }
    }

    fin.close();
    return true;
}

CSRGraph convert_weighted_graph_to_CSR(vector<vector<pair<int, int>>>& adj){
    CSRGraph csr;
    int V = adj.size(); // number of vertices
    csr.row_ptr.push_back(0); // first row pointer is always zero

    for(int nodes=0;nodes<V;nodes++){
        for(auto neighbor : adj[nodes]){
            csr.values.push_back(neighbor.second); // edge weights
            csr.col_idx.push_back(neighbor.first); // populate column indices by adding neighbors to col_idx vector
        }
        // populate row pointers by keeping track of number of edges for each vertex
        csr.row_ptr.push_back(csr.col_idx.size());
    }
    return csr;
}