#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Generate a directed graph with positive capacities
void generate_maxflow_graph(int V, int E){
    string filename = "tests/maxflow_" + to_string(V) + ".txt";
    ofstream fout(filename);

    if(!fout){
        cout << "Cannot create file: " << filename << endl;
        return;
    }

    // Maximum number of directed edges without self-loops
    long long max_edges = 1LL * V * (V - 1);
    if(E > max_edges){
        cout << "Not possible to create the graph as the number of edges exceeds the maximum."<< endl;
        return;
    }

    vector<vector<pair<int, int>>> adj(V);

    int edges = 0;
    
    // create path from source to sink
    for(int u = 0;u<V-1;u++){
        int v = u + 1;
        int capacity = rand() % 50 + 1; // Positive capacity from 1 to 50
        adj[u].push_back({v, capacity});
        edges++;
    }

    // Add remaining edges
    while(edges < E){
        int u = rand() % V;
        int v = rand() % V;

        // Avoid self-loops
        if(u == v){
            continue;
        }

        // Check for duplicate edge u -> v
        bool exists = false;
        for(auto edge : adj[u]){
            if(edge.first == v){
                exists = true;
                break;
            }
        }

        if(exists){
            continue;
        }

        int capacity = rand() % 50 + 1; // Positive capacity from 1 to 50
        adj[u].push_back({v, capacity});
        edges++;
    }

    // Choose source and sink
    int source = 0;
    int sink = V - 1;

    // Write V and E
    fout << V << " " << E << endl;

    // Write adjacency lists to file
    for(int u=0;u<V;u++){
        fout << u << " " << adj[u].size();
        for(auto edge : adj[u]){
            fout << " " << edge.first << " " << edge.second;
        }
        fout << endl;
    }

    // Write source and sink to file
    fout << "SOURCE " << source << endl;
    fout << "SINK " << sink << endl;

    fout.close();
}

int main(){
    generate_maxflow_graph(10, 20);
    generate_maxflow_graph(100, 200);
    generate_maxflow_graph(1000, 2000);
    generate_maxflow_graph(10000, 20000);
    generate_maxflow_graph(50000, 100000);
}