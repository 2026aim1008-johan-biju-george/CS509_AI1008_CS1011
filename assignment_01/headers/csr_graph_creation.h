#ifndef CSR_GRAPH_CREATION_H
#define CSR_GRAPH_CREATION_H

#include <vector>
#include <string>

using namespace std;

struct CSRGraph {
    vector<int> values;
    vector<int> col_idx;
    vector<int> row_ptr;
};

bool read_unweighted_graph(string& filename, vector<vector<int>>& adj, int& V, int& E, int& source);
bool read_weighted_graph(string& filename, vector<vector<pair<int, int>>>& adj, int& V, int& E, int& source);
CSRGraph convert_unweighted_graph_to_CSR(vector<vector<int>>& adj);
CSRGraph convert_weighted_graph_to_CSR(vector<vector<pair<int, int>>>& adj);

#endif