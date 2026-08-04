#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// function to generate unweighted graph and write it to file
void generate_unweighted_graph(string algorithm, int V, int E, int source, bool directed=false){
    string filename = "tests/" + algorithm + "_" + to_string(V) + ".txt"; // input filename
    ofstream fout(filename); // output file pointer
    if(!fout){
        cout << "Cannot create file: "<< filename << endl;
        return;
    }

    // calculate number of maximum edges and check if the number of edges exceeds the maximum possible number of edges without self-loops
    long long max_edges;
    if(directed)
        max_edges = 1LL * V * (V-1);
    else
        max_edges = 1LL * V * (V-1) / 2;

    if(E > max_edges){
        cout << "Not possible to create the graph as the number of edges exceeds the maximum possible number of edges.\n";
        return;
    }

    vector<vector<int>> adj(V); // adjacency list (unweighted graph)

    // First pass: one outgoing edge per vertex (so that the graph is connected)
    int edges = 0;
    for(int u=0;u<V && edges<E;u++){
        int v;
        do {
            v = rand() % V;
        } while (v == u);

        adj[u].push_back(v);
        edges++;
    }

    // Second pass: add remaining random edges
    while(edges < E){
        int u = rand() % V; // random vertex u
        int v = rand() % V; // random vertex v
        
        // check for duplicate edges
        bool exists = false;
        for(auto neighbor : adj[u]){
            if(neighbor == v){
                exists = true;
                break;
            }
        }
        if(!directed){
            for(auto edge : adj[v]){
                if(edge == u){
                    exists = true;
                    break;
                }
            }
        }

        // push the neighbor to adjacency list if it's not a duplicate and not the same as the node itself (to avoid self-loops)
        if(!exists && u != v){
            adj[u].push_back(v);
            if(!directed){
                adj[v].push_back(u);
            }
            edges++;
        }
    }

    fout << V << " " << E << endl; // write number of vertices and edges to file
    
    // write adjacency list to file
    for(int node=0;node<V;node++){
        fout << node << " " << adj[node].size() << " ";

        for(int neighbor : adj[node])
            fout << neighbor << " ";

        fout << endl;
    }
    
    // write source node to file
    fout << "SOURCE " << source << endl;
}

// main function to generate unweighted graph test cases
void generate_unweighted_tests(){
    generate_unweighted_graph("bfs", 10, 20, 0);
    generate_unweighted_graph("bfs", 100, 200, 0);
    generate_unweighted_graph("bfs", 10000, 20000, 0);
    generate_unweighted_graph("bfs", 50000, 100000, 0);
    generate_unweighted_graph("bfs", 100000, 200000, 0);
    generate_unweighted_graph("dfs", 10, 20, 0);
    generate_unweighted_graph("dfs", 100, 200, 0);
    generate_unweighted_graph("dfs", 10000, 20000, 0);
    generate_unweighted_graph("dfs", 50000, 100000, 0);
    generate_unweighted_graph("dfs", 100000, 200000, 0);
}