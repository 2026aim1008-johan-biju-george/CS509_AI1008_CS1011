#include <iostream>
#include <vector>
#include <queue>
#include <chrono>
#include <fstream>
#include <string>
#include <climits>

using namespace std;

// structure to represent graph in Compressed Sparse Row (CSR) format
struct CSRGraph {
    vector<int> values; // weights of edges
    vector<int> col_idx; // column indices of edges
    vector<int> row_ptr; // row pointers for each vertex
};

// function to read unweighted graph from file into adjacency list
bool read_unweighted_graph(string& filename, vector<vector<int>>& adj, int& V, int& E, int& source){
    ifstream fin(filename); // input file pointer
    if(!fin){
        cout << "Cannot open file: " << filename << endl;
        return false;
    }
    
    fin >> V >> E; // read input of number of vertices and edges
    adj.assign(V, vector<int>()); // initialize adjacency list
    // read the adjacency list from file, and populate the adjacency list vector
    for(int i=0;i<V;i++){
        int node, degree;
        fin >> node >> degree;
        for(int j=0;j<degree;j++){
            int neighbor;
            fin >> neighbor;
            adj[node].push_back(neighbor);
        }
    }
    // read the source vertex from file
    string source_label;
    fin >> source_label >> source;

    fin.close();
    return true;
}

// function to read unweighted graph from file into adjacency list
bool read_weighted_graph(string& filename, vector<vector<pair<int, int>>>& adj, int& V, int& E, int& source){
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
    // read the source vertex from file
    string source_label;
    fin >> source_label >> source;

    fin.close();
    return true;
}

// function to convert adjacency list to CSR format
CSRGraph convert_unweighted_graph_to_CSR(vector<vector<int>>& adj){
    CSRGraph csr;
    int V = adj.size(); // number of vertices
    csr.row_ptr.push_back(0); // first row pointer is always zero

    for(int nodes=0;nodes<V;nodes++){
        for(auto neighbor : adj[nodes]){
            csr.values.push_back(1); // assuming unweighted graph, all edges have weight 1
            csr.col_idx.push_back(neighbor); // populate column indices by adding neighbors to col_idx vector
        }
        // populate row pointers by keeping track of number of edges for each vertex
        csr.row_ptr.push_back(csr.col_idx.size());
    }

    return csr;
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