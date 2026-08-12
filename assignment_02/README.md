# Assignment 2 — Graph Algorithms (Triangle Counting, Betweenness Centrality, Connected Components)

## Assignment Details

**Type:** Buddy

**Objective:** Our objective of this assignment is to implement three graph algorithms on **unweighted, undirected graphs**:

- Triangle Counting (TC)
- Betweenness Centrality (BC)
- Connected Components (CC)

The graphs are stored as adjacency lists and converted to **Compressed Sparse Row (CSR)** format before running the algorithms. The CSR conversion is preprocessing and is not included in the reported algorithm execution time. Vertex numbering follows the `0` to `V-1` convention.

The required graph sizes are:

| Algorithm | Required vertices |
|---|---|
| Triangle Counting | 10, 100, 10,000, 50,000, 100,000 |
| Betweenness Centrality | 10, 100, 1,000, 5,000, 10,000 |
| Connected Components | 10, 100, 10,000, 50,000, 100,000 |

The reduced sizes for Betweenness Centrality are due to its higher `O(V x E)` running time.

---

## Algorithms

### Triangle Counting (TC)

It finds the total number of sets of three vertices where every pair is connected by an edge.

The implementation uses the CSR representation. For each vertex, pairs of its neighbours are examined and checked for a connecting edge. Since every triangle can be discovered at each of its three vertices, the raw count is divided by 3 to obtain the final number of triangles. Sorting adjacency lists can improve common-neighbour checks.

### Betweenness Centrality (BC)

It measures how frequently a vertex lies on shortest paths between other pairs of vertices.

For the unweighted graphs in this assignment, **Brandes' algorithm** is used. It performs a BFS from every source vertex and accumulates the dependency values required to calculate the centrality of every vertex. The assignment requires the **raw, unnormalized** centrality values.

### Connected Components (CC)

It identifies maximal groups of vertices where every pair of vertices in the same group is connected by a path.

The implementation uses graph traversal over the CSR representation, starting a new BFS/DFS whenever an unvisited vertex is found. Every vertex, including isolated vertices, receives exactly one component ID.

---

## Input Format

All three algorithms use the same **unweighted undirected adjacency-list format**.

```
V E
u0 degree neighbor1 neighbor2 ...
u1 degree neighbor1 neighbor2 ...
...
u(V-1) degree neighbor1 neighbor2 ...
```

Where:

- `V` = number of vertices.
- `E` = number of undirected edges.
- `u` = vertex number.
- `degree` = number of neighbours of the vertex.
- Each undirected edge must appear in both endpoint adjacency lists.
- An isolated vertex is written as:

```
u 0
```

There is **no `SOURCE` line** for TC, BC, or CC.

Example:

```
6 8
0 2 1 2
1 3 0 2 3
2 3 0 1 3
3 4 1 2 4 5
4 2 3 5
5 2 3 4
```

The graph is unweighted; only vertex IDs are stored in the adjacency lists.

---

## Assumptions and Constraints

- Graphs are **unweighted and undirected**.
- Vertices are numbered from `0` to `V-1`.
- Every undirected edge appears in the adjacency list of both endpoints.
- Isolated vertices are included in the input using `u 0`.
- Each test case is stored in a separate `.txt` file.
- CSR conversion from the previous assignment is reused rather than duplicated.
- CSR conversion is considered preprocessing and is not included in algorithm timing.
- For algorithms using CSR, timing begins only after CSR has been prepared. fileciteturn13file4L296-L321
- The graph generator is used to create test graphs for the three algorithms.
- Betweenness Centrality uses smaller maximum graph sizes because of its `O(VE)` complexity.
- Triangle Counting uses sorted adjacency lists where applicable to make neighbour/common-neighbour checks faster.

---

## Description of Source Files, Header Files, Helper Functions and Test Files

### Source Files

#### `src/connected_components.cpp`

Implements the Connected Components algorithm.

Main responsibility:

- Load the graph in CSR format.
- Traverse all vertices.
- Start a new traversal for every unvisited vertex.
- Assign a component ID to each vertex.
- Report the number of connected components and component IDs.

#### `src/csr.cpp`

Contains CSR-related graph loading/conversion functionality.

The CSR representation contains:

- `row_ptr`
- `col_idx`
- `V`
- `E`

The CSR conversion is preprocessing and is not included in algorithm execution time.

#### `src/generator.cpp`

Generates graph input files for:

- Triangle Counting
- Betweenness Centrality
- Connected Components

The generated graphs follow the required unweighted undirected adjacency-list format.

#### `src/triangle_counting.cpp`

Implements Triangle Counting using the CSR graph.

It:

1. Processes neighbour pairs.
2. Checks whether the corresponding neighbour pair is connected.
3. Counts discovered triangles.
4. Corrects the raw count because each triangle is discovered three times.
5. Reports the total triangle count and execution time.

### Header Files

#### `headers/algorithms.hpp`

Declares the three algorithm driver functions:

```
void runTriangleCounting(const string& filename);

void runConnectedComponents(const string& filename);

void runBetweennessCentrality(const string& filename);
```

#### `headers/graph.hpp`

Defines the CSR graph structure:

```
struct CSRGraph {
    int V;
    int E;
    vector<int> row_ptr;
    vector<int> col_idx;
};
```

and declares:

```
CSRGraph loadCSR(const string& filename);
```

### Test Files

Generated graph files are stored in the `tests/` directory.

The filenames identify the algorithm and graph size. For example:

```
tc_10.txt
tc_100.txt
cc_10.txt
cc_100.txt
bc_10.txt
bc_100.txt
```

The exact filenames may depend on the naming used in `src/generator.cpp`.

---

## 6. Compilation

Compile the source files together with the required headers and CSR functionality.

From the `assignment_02` directory,

```
g++ src/generator.cpp -o generator.exe

g++ driver/main.cpp src/connected_components.cpp src/csr.cpp src/triangle_counting.cpp src/betweenness_centrality.cpp -o assignment2.exe
```

---

## 7. Execution

Run the compiled executables:

```
./generator
./assignment2
```

On Windows:

```
.\generator.exe
.\assignment2.exe
```

The program then allows the required algorithm/test case to be selected or executed according to the implemented driver.

---

## Execution Steps

### Step 1 — Generate Test Graphs

Run the graph generator to create the required test files.

The graphs are unweighted and undirected.

### Step 2 — Load the Graph

The input adjacency list is read from the corresponding `.txt` file.

### Step 3 — Convert to CSR

The adjacency-list representation is converted into CSR.

This preprocessing time is excluded from the algorithm timing as required by the assignment.

### Step 4 — Run the Algorithm

Run one of:

- Triangle Counting
- Betweenness Centrality
- Connected Components

### Step 5 — Record Output

Record:

- Input graph size
- Number of edges
- Algorithm result
- Execution time

### Step 6 — Repeat

Repeat for all required graph sizes for the corresponding algorithm.

---

## 9. Performance Measurement

Execution time is measured using C++ high-resolution timing, for example:

```
auto start = chrono::high_resolution_clock::now();

algorithm();

auto end = chrono::high_resolution_clock::now();

auto duration =
    chrono::duration<double, milli>(end - start).count();
```

The timer starts **after CSR conversion** so that preprocessing is not included in the algorithm runtime.

---

## 10. Expected and Actual Outputs

### Triangle Counting

The expected output contains the total number of triangles. For the two smallest graph sizes, listing the individual triangles is also required.

Example:

```
Algorithm: Triangle Counting
Total triangles: 3
Triangles found:
(0, 1, 2)
(1, 2, 3)
(3, 4, 5)
Execution time: <value> ms
```

The actual output should contain the triangle count produced by the implementation and the measured execution time.

### Betweenness Centrality

The output contains the raw centrality value for every vertex, printed to two decimal places.

Example:

```
Algorithm: Betweenness Centrality
Vertex Centrality
0 0.00
1 3.00
2 4.00
3 3.00
4 0.00
Execution time: <value> ms
```

### Connected Components

The output contains:

- Total number of connected components.
- Component ID assigned to every vertex.

Component IDs start at `0` and are assigned in the order components are first discovered.

Example:

```
Algorithm: Connected Components
Total components: <value>
Vertex Component
0 0
1 0
2 0
3 0
4 1
5 1
6 2
7 3
Execution time: <value> ms
```

### Actual Results

The following table can be updated with the actual measured results:

## Results

| Algorithm | Test File | Vertices (V) | Edges (E) | Expected Output | Actual Output | Execution Time (ms) | Status |
| :--- | :--- | :---: | :---: | :--- | :--- | :---: | :---: |
| **Triangle Counting** | tc_10.txt | 10 | 15 | Total triangles & details | Total triangles: 22 | 0.016 ms | Pass |
| **Triangle Counting** | tc_100.txt | 100 | 150 | Total triangles & details | Total triangles: 292 | 0.2016 ms | Pass |
| **Triangle Counting** | tc_10000.txt | 10,000 | 15,000 | Total triangles count | Total triangles: 29992 | 0.9964 ms | Pass |
| **Triangle Counting** | tc_50000.txt | 50,000 | 75,000 | Total triangles count | Total triangles: 149992 | 6.9795 ms | Pass |
| **Triangle Counting** | tc_100000.txt | 100,000 | 150,000 | Total triangles count | Total triangles: 299992 | 15.9558 ms | Pass |
| **Connected Components** | cc_10.txt | 10 | 7 | Component per vertex | Components count: 3, Vertex IDs mapped | 0.0123 ms | Pass |
| **Connected Components** | cc_100.txt | 100 | 97 | Component per vertex | Components count: 3, Vertex IDs mapped | 0.0325 ms | Pass |
| **Connected Components** | cc_10000.txt | 10,000 | 9,997 | Component per vertex | Components count: 3, Vertex IDs mapped  | 0.9683 ms | Pass |
| **Connected Components** | cc_50000.txt | 50,000 | 49,997 | Component per vertex | Components count: 3, Vertex IDs mapped  | 5.976 ms | Pass |
| **Connected Components** | cc_100000.txt | 100,000 | 99,997 | Component per vertex | Components count: 3, Vertex IDs mapped  | 11.9644 ms | Pass |
| **Betweenness Centrality** | bc_10.txt | 10 | 15 | Centrality per vertex | Centrality: 9.00 | 0.16 ms | Pass |
| **Betweenness Centrality** | bc_100.txt | 100 | 150 | Centrality per vertex | Centrality: 1584.00 | 8.46 ms | Pass |
| **Betweenness Centrality** | bc_10000.txt | 10,000 | 15,000 | Centrality per vertex | Centrality: 16658334.00  | 43237.77 ms | Pass |

---

## 11. Performance Analysis

The three algorithms have different computational characteristics.

### Triangle Counting

Triangle Counting performs neighbour/common-neighbour checks. Sorting adjacency lists helps make these checks faster. The runtime increases as the number of vertices and edges increases.

### Betweenness Centrality

Betweenness Centrality is the most expensive of the three algorithms for large graphs because Brandes' algorithm performs a BFS from every source vertex. Its running time is `O(V x E)`.

Therefore, the assignment specifies smaller graph sizes for BC:

```
10, 100, 1,000, 5,000, 10,000
```

### Connected Components

Connected Components requires a traversal of the graph and therefore scales much better than BC for sparse graphs. Its running time is `O(V + E)`.

The full graph-size scale is therefore used:

```
10, 100, 10,000, 50,000, 100,000
```

---

## 12. Complexity (Time and Space)

Let `V` be the number of vertices and `E` the number of undirected edges.

| Algorithm | Time Complexity | Space Complexity |
|---|---|---|
| Triangle Counting | Depends on neighbour-pair/common-neighbour implementation; approximately `O(Σ deg(v)^2)` for pair checking | `O(V + E)` |
| Betweenness Centrality | `O(V x E)` | `O(V + E)` |
| Connected Components | `O(V + E)` | `O(V + E)` |

The assignment specifically states `O(V x E)` for Brandes-based Betweenness Centrality.

The CSR representation requires linear storage in the graph size, using `row_ptr` and `col_idx`.

---

## 13. References

1. Connected Components: [https://en.wikipedia.org/wiki/Component_(graph_theory)](https://en.wikipedia.org/wiki/Component_(graph_theory))
2. Betweenness Centrality: [https://en.wikipedia.org/wiki/Betweenness_centrality](https://en.wikipedia.org/wiki/Betweenness_centrality)