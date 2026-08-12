#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <string>

using namespace std;

struct CSRGraph {
    int V;
    int E;
    vector<int> row_ptr;
    vector<int> col_idx;
};

CSRGraph loadCSR(const string& filename);

#endif