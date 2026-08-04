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
bool read_graph(string& filename, vector<vector<pair<int, int>>>& adj, int& V, int& E, int& source){
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
CSRGraph convert_to_CSR(vector<vector<pair<int, int>>>& adj){
    CSRGraph csr;
    int V = adj.size(); // number of vertices
    csr.row_ptr.push_back(0); // first row pointer is always zero

    for(int nodes=0;nodes<V;nodes++){
        for(auto neighbor : adj[nodes]){
            csr.values.push_back(neighbor.second); // populate values with edge weights
            csr.col_idx.push_back(neighbor.first); // populate column indices by adding neighbors to col_idx vector
        }
        // populate row pointers by keeping track of number of edges for each vertex
        csr.row_ptr.push_back(csr.col_idx.size());
    }

    return csr;
}

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
    if(!read_graph(filename, adj, V, E, source)){
        cout << "Error reading graph from file: " << filename << endl;
        return;
    }

    CSRGraph csr = convert_to_CSR(adj); // convert adjacency list to CSR format
    run_SSSP(csr, V, source);
}