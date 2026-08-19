#include "../headers/maxflow.h"
#include "../headers/csr_graph_creation.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <chrono>
#include <climits>
#include <algorithm>

using namespace std;

bool read_maxflow_graph(string& filename, vector<vector<pair<int, int>>>& adj, int& V, int& E, int& source, int& sink){
    ifstream fin(filename);

    if(!fin){
        cout << "Cannot open file: " << filename << endl;
        return false;
    }

    // Read number of vertices and edges
    fin >> V >> E;

    adj.assign(V, vector<pair<int, int>>());

    // Read adjacency list
    for(int i=0;i<V;i++){
        int node;
        int degree;

        fin >> node >> degree;

        for(int j=0;j<degree;j++){
            int neighbor;
            int capacity;

            fin >> neighbor >> capacity;

            adj[node].push_back({neighbor, capacity});
        }
    }

    // Read source
    string source_label;
    fin >> source_label >> source;

    // Read sink
    string sink_label;
    fin >> sink_label >> sink;

    fin.close();
    return true;
}

void add_edge(int u, int v, int capacity, vector<vector<int>>& to, vector<vector<int>>& residual, vector<vector<int>>& reverse_edge){
    int forward_index = to[u].size();
    int reverse_index = to[v].size();

    to[u].push_back(v);
    residual[u].push_back(capacity);
    reverse_edge[u].push_back(reverse_index);

    to[v].push_back(u);
    residual[v].push_back(0);
    reverse_edge[v].push_back(forward_index);
}

void build_residual_graph(int V, CSRGraph& csr, vector<vector<int>>& to, vector<vector<int>>& residual, vector<vector<int>>& reverse_edge){
    to.resize(V);
    residual.resize(V);
    reverse_edge.resize(V);

    for(int u=0;u<V;u++){
        int start = csr.row_ptr[u];
        int end = csr.row_ptr[u + 1];

        for(int i=start;i<end;i++){
            int v = csr.col_idx[i];
            int capacity = csr.values[i];
            add_edge(u, v, capacity, to, residual, reverse_edge);
        }
    }
}

bool bfs(int V, int source, int sink, vector<vector<int>>& to, vector<vector<int>>& residual, vector<int>& level){
    level.assign(V, -1);
    queue<int> q;

    level[source] = 0;
    q.push(source);

    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(int i=0;i<to[u].size();i++){
            int v = to[u][i];
            if(residual[u][i] > 0 && level[v] == -1){
                level[v] = level[u] + 1;
                q.push(v);
            }
        }
    }
    return level[sink] != -1;
}

int dfs(int u, int sink, int flow, vector<vector<int>>& to, vector<vector<int>>& residual, vector<vector<int>>& reverse_edge, vector<int>& level, vector<int>& ptr){
    if(u == sink){
        return flow;
    }

    while(ptr[u] < to[u].size()){
        int i = ptr[u];
        int v = to[u][i];

        if(residual[u][i] > 0 && level[v] == level[u] + 1){
            int new_flow = min(flow, residual[u][i]);
            int pushed = dfs(v, sink, new_flow, to, residual, reverse_edge, level, ptr);
            if(pushed > 0){
                residual[u][i] -= pushed;
                int reverse = reverse_edge[u][i];
                residual[v][reverse] += pushed;
                return pushed;
            }
        }
        ptr[u]++;
    }
    return 0;
}

int find_maxflow(int V, CSRGraph& csr, int source, int sink, vector<vector<int>>& to, vector<vector<int>>& residual, vector<vector<int>>& reverse_edge){
    // Build residual graph
    build_residual_graph(V, csr, to, residual, reverse_edge);

    vector<int> level(V);
    vector<int> ptr(V);

    int max_flow = 0;

    // Build level graph
    while(bfs(V, source, sink, to, residual, level)){
        ptr.assign(V, 0);
        // Send blocking flow
        while(true){
            int pushed = dfs(source, sink, INT_MAX, to, residual, reverse_edge, level, ptr);
            if(pushed == 0){
                break;
            }
            max_flow += pushed;
        }
    }
    return max_flow;
}

vector<int> find_source_side(int V, int source, vector<vector<int>>& to, vector<vector<int>>& residual){
    vector<int> visited(V, 0);
    queue<int> q;

    q.push(source);
    visited[source] = 1;

    while(!q.empty()){
        int u = q.front();
        q.pop();

        for(int i=0;i<to[u].size();i++){
            int v = to[u][i];
            if(residual[u][i] > 0 && visited[v] == 0){
                visited[v] = 1;
                q.push(v);
            }
        }
    }
    return visited;
}

vector<vector<int>> find_cut_edges(int V, CSRGraph& csr, vector<int>& visited){
    vector<vector<int>> cut_edges;

    for(int u=0;u<V;u++){
        int start = csr.row_ptr[u];
        int end = csr.row_ptr[u + 1];

        for(int i=start;i<end;i++){
            int v = csr.col_idx[i];
            int capacity = csr.values[i];
            if(visited[u] == 1 && visited[v] == 0){
                cut_edges.push_back({u, v, capacity});
            }
        }
    }
    return cut_edges;
}

void maxflow_dinic(int V, CSRGraph& csr, int source, int sink, vector<vector<int>>& to, vector<vector<int>>& residual, 
                vector<vector<int>>& reverse_edge, vector<int>& source_side, vector<vector<int>>& cut_edges, int& maxflow, int& min_cut_capacity){

    maxflow = find_maxflow(V, csr, source, sink, to, residual, reverse_edge);
    source_side = find_source_side(V, source, to, residual);
    cut_edges = find_cut_edges(V, csr, source_side);

    for(auto edge : cut_edges){
        min_cut_capacity += edge[2];
    }
}

void run_maxflow_test(){
    int V, E, source, sink;
    int maxflow = 0, min_cut_capacity = 0;
    vector<vector<int>> to, residual, reverse_edge, cut_edges;
    vector<int> source_side;

    string filename;
    cout << "Enter input filename: ";
    cin >> filename;

    vector<vector<pair<int, int>>> adj;
    if(!read_maxflow_graph(filename, adj, V, E, source, sink)){
        cout << "Error reading graph from file: " << filename << endl;
        return;
    }

    CSRGraph csr = convert_weighted_graph_to_CSR(adj);

    auto start_time = chrono::high_resolution_clock().now();
    maxflow_dinic(V, csr, source, sink, to, residual, reverse_edge, source_side, cut_edges, maxflow, min_cut_capacity);
    auto end_time = chrono::high_resolution_clock().now();

    auto duration = chrono::duration<double, milli>(end_time - start_time).count();
    
    cout << "\nAlgorithm: Maxflow-Mincut" << endl;
    cout << "Maximum flow: " << maxflow << endl;
    cout << "Minimum cut capacity: " << min_cut_capacity << endl;
    if(V < 10000){
        cout << "Source side: ";
        for(int i=0;i<V;i++){
            if(source_side[i] == 1){
                cout << i << " ";
            }
        }
        cout << endl;

        cout << "Sink side: ";
        for(int i=0;i<V;i++){
            if(source_side[i] == 0){
                cout << i << " ";
            }
        }
        cout << endl;

        cout << "Cut edges:\n";
        for(auto edge : cut_edges){
            cout << edge[0] << " " << edge[1] << " " << edge[2] << endl;
        }
    }
    cout << "Execution time: " << duration << " ms" << endl;
}