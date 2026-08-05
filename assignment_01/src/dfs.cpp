#include "../headers/csr_graph_creation.h"
#include <iostream>
#include <vector>
#include <queue>
#include <chrono>
#include <fstream>
#include <string>
#include <stack>
#include <climits>

using namespace std;

// helper function for DFS
void DFS(int source, const CSRGraph& graph, vector<bool>& visited, vector<int>& traversal) {
    stack<int> st;
    st.push(source);
    visited[source] = true; 

    while (!st.empty()) {
        int node = st.top();
        st.pop();

        traversal.push_back(node);

        int start_edge = graph.row_ptr[node];
        int end_edge = graph.row_ptr[node + 1];

        // Push neighbors in reverse order to obtain same traversal order as recursive DFS
        for (int i = end_edge - 1; i >= start_edge; i--) {
            int neighbor = graph.col_idx[i];
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                st.push(neighbor);
            }
        }
    }
}

// function to run DFS on CSR graph
void run_DFS(CSRGraph& graph, int V, int source) {
    double total_time = 0;
    int runs = (V <= 100)? 100 : 1; // assuming no. of nodes <= 100 are considered 'fast inputs', let's take the average execution time over 100 runs
    vector<int> traversal;
    
    for(int r=0;r<runs;r++){
        vector<bool> visited(V, false); // initialise visited vector for every run
        traversal.clear(); // reset traversal vector for every run
        
        auto start_time = chrono::high_resolution_clock::now(); // Start timer for DFS
        DFS(source, graph, visited, traversal);
        auto end_time = chrono::high_resolution_clock::now(); // End timer for DFS
        
        total_time += chrono::duration<double, milli>(end_time - start_time).count();
    }

    // cout << "Algorithm: DFS\nSource: " << source << "\nTraversal: ";
    // for(int node : traversal){
    //     cout << node << " ";
    // }
    cout << "\nExecution time: " << total_time/runs << " ms\n\n";
}

void run_DFS_test(){
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
    run_DFS(csr, V, source);
}