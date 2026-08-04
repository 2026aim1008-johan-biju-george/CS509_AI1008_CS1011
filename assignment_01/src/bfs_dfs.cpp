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

// function to read graph from file and populate adjacency list
bool read_graph(string& filename, vector<vector<int>>& adj, int& V, int& E, int& source){
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

// function to convert adjacency list to CSR format
CSRGraph convert_to_CSR(vector<vector<int>>& adj){
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
    
    cout << "Algorithm: BFS\nSource: " << source << "\nTraversal: ";
    for (int node : traversal){
        cout << node << " ";
    }
    cout << "\nDistances:\n";
    for (int i=0;i<V;i++){
        if(distance[i]==INT_MAX){ 
            cout << i << " INF\n";
        }
        else{
            cout << i << " " << distance[i] << "\n";
        }
    }
    cout << "Execution time: " << total_time/runs << " ms\n\n";
}

// helper function for DFS
void DFS(int node, const CSRGraph& graph, vector<bool>& visited, vector<int>& traversal) {
    visited[node] = true;
    traversal.push_back(node);
    int start_edge = graph.row_ptr[node];
    int end_edge = graph.row_ptr[node+1];
    for(int i = start_edge; i < end_edge; i++){
        int neighbor = graph.col_idx[i];
        if(!visited[neighbor]){
            DFS(neighbor, graph, visited, traversal);
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

    cout << "Algorithm: DFS\nSource: " << source << "\nTraversal: ";
    for(int node : traversal){
        cout << node << " ";
    }
    cout << "\nExecution time: " << total_time/runs << " ms\n\n";
}

void run_BFS_DFS(){
    int V, E, source; // number of vertices and edges, and source node
    string filename; // input filename
    vector<vector<int>> adj; // adjacency list (unweighted graph)

    cout << "Enter input filename: ";
    cin >> filename;
    
    // read graph from file and populate adjacency list
    if(!read_graph(filename, adj, V, E, source)){
        cout << "Error reading graph from file: " << filename << endl;
        return;
    }

    CSRGraph csr = convert_to_CSR(adj); // convert adjacency list to CSR format
    run_BFS(csr, V, source);
    run_DFS(csr, V, source);
}