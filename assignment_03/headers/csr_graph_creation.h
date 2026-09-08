#ifndef CSR_GRAPH_CREATION_H
#define CSR_GRAPH_CREATION_H

#include <vector>
#include <string>

using namespace std;

struct CSRGraph{
    vector<int> values;
    vector<int> col_idx;
    vector<int> row_ptr;
};

bool read_weighted_graph(string& filename, vector<vector<pair<int, int>>>& adj, int& V, int& E);
CSRGraph convert_weighted_graph_to_CSR(vector<vector<pair<int, int>>>& adj);

#endif