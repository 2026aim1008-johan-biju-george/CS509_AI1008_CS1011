#include "../headers/graph.hpp"
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

CSRGraph loadCSR(const string& filename){
    ifstream infile(filename);
    if(!infile.is_open()){
        cerr << "Error: Could not open input file " << filename << endl;
        exit(1);
    }

    int V, E;
    infile >> V >> E;
    vector<int> row_ptr;
    vector<int> col_idx;
    row_ptr.push_back(0);

    for(int i=0;i<V;i++){
        int u, degree;
        infile >> u >> degree;
        vector<int> neighbors(degree);
        for(int j = 0; j < degree; j++){
            infile >> neighbors[j];
        }
        // sorting neighbor lists for fast linear scan
        sort(neighbors.begin(), neighbors.end());
        for(int n : neighbors){
            col_idx.push_back(n);
        }
        row_ptr.push_back(col_idx.size());
    }
    infile.close();

    return {V, E, row_ptr, col_idx};
}