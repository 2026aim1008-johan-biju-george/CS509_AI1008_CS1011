#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

// Helper function for to_string compatibility in older GCC versions
template <typename T>
string toString(T val) {
    stringstream ss;
    ss << val;
    return ss.str();
}

// Generates valid Triangle Counting format (unweighted undirected adjacency list)
void generateTCInput(int V, const string& filename) {
    ofstream outfile(filename.c_str());
    if (!outfile.is_open()) {
        cerr << "Error creating file: " << filename << endl;
        return;
    }

    int E = (V * 3) / 2;
    outfile << V << " " << E << "\n";

    for (int i = 0; i < V; ++i) {
        int n1 = (i + 1) % V;
        int n2 = (i + 2) % V;
        int n3 = (i + 3) % V;
        outfile << i << " 3 " << n1 << " " << n2 << " " << n3 << "\n";
    }
    outfile.close();
}

// Generates valid Betweenness Centrality format (unweighted undirected adjacency list)
void generateBCInput(int V, const string& filename) {
    ofstream outfile(filename.c_str());
    if (!outfile.is_open()) {
        cerr << "Error creating file: " << filename << endl;
        return;
    }

    int E = (V * 3) / 2;
    outfile << V << " " << E << "\n";

    for (int i = 0; i < V; ++i) {
        int n1 = (i + 1) % V;
        int n2 = (i + 2) % V;
        int n3 = (i + 3) % V;
        outfile << i << " 3 " << n1 << " " << n2 << " " << n3 << "\n";
    }
    outfile.close();
}

// Generates valid Connected Components format
void generateCCInput(int V, const string& filename) {
    ofstream outfile(filename.c_str());
    if (!outfile.is_open()) {
        cerr << "Error creating file: " << filename << endl;
        return;
    }

    int isolated_count = (V >= 10) ? 2 : 0;
    int active_V = V - isolated_count;
    int E = (active_V > 1) ? active_V - 1 : 0;

    outfile << V << " " << E << "\n";

    for (int i = 0; i < active_V; ++i) {
        if (active_V == 1) {
            outfile << i << " 0\n";
        } else if (i == 0) {
            outfile << i << " 1 " << (i + 1) << "\n";
        } else if (i == active_V - 1) {
            outfile << i << " 1 " << (i - 1) << "\n";
        } else {
            outfile << i << " 2 " << (i - 1) << " " << (i + 1) << "\n";
        }
    }

    for (int i = active_V; i < V; ++i) {
        outfile << i << " 0\n"; // Isolated vertex
    }
    outfile.close();
}

int main() {
    int sizes[] = {10, 100, 10000, 50000, 100000};
    
    for (int i = 0; i < 5; ++i) {
        int v = sizes[i];
        generateTCInput(v, "tests/tc_" + toString(v) + ".txt");
        generateCCInput(v, "tests/cc_" + toString(v) + ".txt");
        generateBCInput(v, "tests/bc_" + toString(v) + ".txt");
    }
    cout << "All test files successfully generated\n";
}