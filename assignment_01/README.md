# Assignment 1: Graph Traversals (BFS, DFS, SSSP)

## Assignment Details

**Type:** Buddy

**Objective:**
The objective of this assignment is to implement and compare graph traversal algorithms:

1. Breadth-First Search (BFS)
2. Depth-First Search (DFS)
3. Single-Source Shortest Path (SSSP)

The assignment measures the execution time of these implementations for graphs of different sizes.

---

## Algorithms

### 1. Breadth-First Search (BFS)

Breadth-First Search (BFS) is a graph traversal algorithm that explores vertices level by level, starting from a specified source vertex. It uses a queue to ensure that all neighbours of the current vertex are visited before moving to the next level.

In this implementation:

* The input graph is first converted from an adjacency-list representation to the Compressed Sparse Row (CSR) format.
* A queue is used to process vertices in First-In-First-Out (FIFO) order.
* A `visited` array prevents revisiting vertices.
* The traversal order is recorded and printed after the algorithm completes.
* The execution time reported includes only the BFS traversal and excludes graph loading and CSR conversion.

---

### 2. Depth-First Search (DFS)

Depth-First Search (DFS) explores a graph by visiting one path as deeply as possible before backtracking. This implementation uses a recursive approach to traverse the graph.

In this implementation:

* The graph is represented in CSR format.
* Starting from the source vertex, each unvisited neighbour is recursively explored.
* A `visited` array ensures that each vertex is processed only once.
* The traversal order is stored and printed after the traversal completes.
* Only the DFS execution time is measured.

---

### 3. Single-Source Shortest Path (SSSP)

The Single-Source Shortest Path (SSSP) problem is solved using Dijkstra's algorithm, which computes the minimum distance from a given source vertex to every other vertex in a graph with positive edge weights.

In this implementation:

* The graph is converted into CSR format before execution.
* A priority queue (min-heap) is used to efficiently select the vertex with the minimum tentative distance.
* Distance values are updated whenever a shorter path is found.
* After completion, the shortest distance from the source to every reachable vertex is displayed.
* As specified in the assignment, only the algorithm execution time is measured, excluding CSR conversion and file I/O.

---

### CSR Representation

All graph algorithms operate on the Compressed Sparse Row (CSR) representation of the graph.

The CSR format consists of three arrays:

* **row_ptr** – Stores the starting index of each vertex's adjacency list.
* **col_idx** – Stores the destination vertices for every edge.
* **values** – Stores edge weights (used only for weighted graphs such as SSSP).

Using CSR reduces memory usage for sparse graphs and improves traversal efficiency by storing adjacency information in contiguous memory.

---

## Input Format, Assumptions, and Constraints

### Input Format

#### BFS and DFS Input Format

Each test case is stored as a separate text file in adjacency-list format.

```
V E
u0 degree neighbor1 neighbor2 ...
u1 degree neighbor1 neighbor2 ...
...
u(V-1) degree neighbor1 neighbor2 ...
SOURCE s
```

Where:

* **V** – Number of vertices.
* **E** – Number of edges.
* **u** – Vertex whose adjacency list is specified.
* **degree** – Number of adjacent vertices.
* **SOURCE s** – Source vertex from which the traversal begins.

---

#### SSSP Input Format

Each weighted graph is stored as a positive-weighted adjacency list.

```
V E
u0 degree neighbor1 weight1 neighbor2 weight2 ...
u1 degree neighbor1 weight1 neighbor2 weight2 ...
...
u(V-1) degree neighbor1 weight1 neighbor2 weight2 ...
SOURCE s
```

Where:

* **V** – Number of vertices.
* **E** – Number of edges.
* **neighbor** – Adjacent vertex.
* **weight** – Positive edge weight.
* **SOURCE s** – Source vertex for computing shortest paths.

---

### Assumptions

* Graph vertices are numbered from **0** to **V−1**.
* Every test case is stored in a separate text file.
* The graph input is initially provided as an adjacency list and converted to CSR format before executing the algorithms.
* The adjacency-list-to-CSR conversion time is **not** included in the reported execution time.
* BFS and DFS operate on unweighted graphs.
* SSSP operates only on graphs with positive edge weights.
* Input files are assumed to follow the specified format without errors.
* The source vertex specified in the input file is valid.

---

### Constraints

* Graph sizes tested:

  * **10 vertices**
  * **100 vertices**
  * **10,000 vertices**
  * **50,000 vertices**
  * **100,000 vertices**
* The number of edges varies depending on the generated graph and is recorded for every test case.
* Edge weights used in SSSP are strictly positive.
* Execution time reported includes only the execution of BFS, DFS, or SSSP, excluding:

  * File reading
  * Input parsing
  * Graph generation
  * CSR conversion
  * Output printing


## Description of Source Files, Driver Files, Helper Functions, and Test Files

### Driver File (stored in `driver/`)

| File       | Description                                                                                                                                                                                                                                                                      |
| ---------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `driver.cpp` | Menu-driven driver program that serves as the entry point of the application. It allows the user to generate graph test cases and perform graph traversals by invoking the appropriate module functions. |

### Source Files (stored in `src/`)

| File                           | Description                                                                                                                                     |
| ------------------------------ | ----------------------------------------------------------------------------------------------------------------------------------------------- |
| `bfs.cpp`                      | Implements the BFS traversal for unweighted graphs, and measures execution time.                       |
| `dfs.cpp`                      | Implements the DFS traversal for unweighted graphs, and measures execution time.                       |
| `sssp.cpp`                     | Implements the SSSP traversal for weighted graphs using Dijkstra's Algorithm, and measures execution time.            |
| `generate_unweighted_graph.cpp`| Generates unweighted graph test cases with varying numbers of vertices and edges.                                                               |
| `generate_weighted_graph.cpp`  | Generates weighted graph test cases with varying numbers of vertices and edges.                                                                 |
| `csr_graph_creation.cpp`    | Reads graph input files and converts the graph from an adjacency list format to the Compressed Sparse Row (CSR) representation.                      |

### Header Files (stored in `headers/`)

| File                      | Description                                                                               |
| ------------------------- | ----------------------------------------------------------------------------------------- |
| `bfs.h`                   | Function declarations for BFS traversal.                                                  |
| `dfs.h`                   | Function declarations for DFS traversal.                                                  |
| `sssp.h`                  | Function declarations for SSSP traversal.                                                 |
| `graph_generator.h`       | Function declarations for weighted and unweighted graph generation.                       |
| `csr_graph_creation.h`    | Function declarations for reading graph inputs and conversion to CSR format.              |

### Helper Functions

| Function                            | Description                                                                                    |
| ----------------------------------- | ---------------------------------------------------------------------------------------------- |
| `convert_unweighted_graph_to_CSR()` | Converts unweighted graph from adjacency list into CSR format.                                 |
| `convert_weighted_graph_to_CSR()`   | Converts weighted graph from adjacency list into CSR format.                                   |
| `read_unweighted_graph()`           | Reads unweighted graph inputs and populates adjacency list.                                    |
| `read_weighted_graph()`             | Reads weighted graph inputs and populates adjacency list.                                      |
| `run_BFS_test()`                    | Executes BFS implementation and reports execution time.                                        |
| `run_DFS_test()`                    | Executes DFS implementation and reports execution time.                                        |
| `run_SSSP_test()`                   | Executes SSSP implementation and reports execution time.                                       |
| `generate_unweighted_tests()`       | Generates random unweighted graph test cases.                                                  |
| `generate_weighted_tests()`         | Generates random weighted graph test cases.                                                    |

### Test Files (stored in `tests/`)

| Directory/File | Description                                                                                                   |
| -------------- | ------------------------------------------------------------------------------------------------------------- |
| `bfs_xx.txt`   | Contains the number of vertices, number of edges, and the adjacency list (unweighted) used for BFS traversal. |
| `dfs_xx.txt`   | Contains the number of vertices, number of edges, and the adjacency list (unweighted) used for DFS traversal. |
| `sssp_xx.txt`  | Contains the number of vertices, number of edges, and the adjacency list (weighted) used for SSSP traversal.  |

---

## Test Cases

The following graph parameters were tested:

| Test Case | Number of Vertices (V)  | Number of Edges (E) |
| --------- | ----------------------- | ------------------- |
| 1         | 10                      |  20                 |
| 2         | 100                     |  200                |
| 3         | 10000                   |  20000              |
| 4         | 50000                   |  100000             |
| 5         | 100000                  |  200000             |

---

## Compilation and Execution Instructions

### Compilation

Compile all source files together using the following command:

```
g++ driver/driver.cpp src/*.cpp -o assignment1.exe
```

---

### Execution

Run the generated executable.

**Linux/macOS**

```
./assignment1
```

**Windows**

```
assignment1.exe
```
---

### Execution Steps

1. Compile the project.
2. Run the executable.
3. Generate the required graph test files.
4. Select the desired algorithm (BFS, DFS, or SSSP).
5. Enter the required input file or choose the appropriate test case.
6. The program converts the adjacency-list input into CSR format.
7. The selected algorithm is executed.
8. The traversal (BFS/DFS) or shortest-path distances (SSSP) and the algorithm execution time are displayed.

---

### Performance Measurement

The reported execution time includes **only the execution of the selected algorithm**.

The following operations are excluded from the measured time:

* Reading the input file
* Parsing the input
* Graph generation
* Adjacency-list to CSR conversion
* Output printing

---

## Expected and Actual Outputs

### BFS
- **Expected Output:**
  - A valid BFS traversal starting from the specified source vertex.
  - The shortest distance (in terms of number of edges) from the source to every reachable vertex.
  - Unreachable vertices should be reported as `INF`.
- **Actual Output:**
  - The program produced a valid BFS traversal and correctly computed distances for all reachable vertices. Unreachable vertices, if any, were reported as `INF`.

### DFS
- **Expected Output:**
  - A valid DFS traversal starting from the specified source vertex.
  - Every reachable vertex should be visited exactly once.
- **Actual Output:**
  - The program produced a valid DFS traversal, visiting every reachable vertex exactly once.

### SSSP
- **Expected Output:**
  - The shortest path distance from the source vertex to every other reachable vertex in the weighted graph.
  - Unreachable vertices should be reported as `INF`.
- **Actual Output:**
  - The program correctly computed the shortest path distances using Dijkstra's algorithm. Unreachable vertices, if any, were reported as `INF`.

---

## Results

| Algorithm | Test File         | Vertices (V) | Edges (E) | Input Type                       | Source Vertex | Expected Output            | Actual Output              | Execution Time (ms) | Status |
| --------- | ----------------- | -----------: | --------: | -------------------------------- | :-----------: | -------------------------- | -------------------------- | ------------------: | :----: |
| BFS       | `bfs_10.txt`      |           10 |        20 | Unweighted Adjacency List        |       0       | Valid BFS Traversal        | Valid BFS Traversal        |            0.002782 |  Pass  |
| DFS       | `dfs_10.txt`      |           10 |        20 | Unweighted Adjacency List        |       0       | Valid DFS Traversal        | Valid DFS Traversal        |            0.004451 |  Pass  |
| SSSP      | `sssp_10.txt`     |           10 |        20 | Positive Weighted Adjacency List |       0       | Correct Shortest Distances | Correct Shortest Distances |              0.0151 |  Pass  |
| BFS       | `bfs_100.txt`     |          100 |       200 | Unweighted Adjacency List        |       0       | Valid BFS Traversal        | Valid BFS Traversal        |            0.043229 |  Pass  |
| DFS       | `dfs_100.txt`     |          100 |       200 | Unweighted Adjacency List        |       0       | Valid DFS Traversal        | Valid DFS Traversal        |            0.037512 |  Pass  |
| SSSP      | `sssp_100.txt`    |          100 |       200 | Positive Weighted Adjacency List |       0       | Correct Shortest Distances | Correct Shortest Distances |              0.0805 |  Pass  |
| BFS       | `bfs_10000.txt`   |        10000 |     20000 | Unweighted Adjacency List        |       0       | Valid BFS Traversal        | Valid BFS Traversal        |              2.7712 |  Pass  |
| DFS       | `dfs_10000.txt`   |        10000 |     20000 | Unweighted Adjacency List        |       0       | Valid DFS Traversal        | Valid DFS Traversal        |              3.0361 |  Pass  |
| SSSP      | `sssp_10000.txt`  |        10000 |     20000 | Positive Weighted Adjacency List |       0       | Correct Shortest Distances | Correct Shortest Distances |              13.65 |  Pass  |
| BFS       | `bfs_50000.txt`   |        50000 |    100000 | Unweighted Adjacency List        |       0       | Valid BFS Traversal        | Valid BFS Traversal        |              5.027 |  Pass  |
| DFS       | `dfs_50000.txt`   |        50000 |    100000 | Unweighted Adjacency List        |       0       | Valid DFS Traversal        | Valid DFS Traversal        |              5.9364 |  Pass  |
| SSSP      | `sssp_50000.txt`  |        50000 |    100000 | Positive Weighted Adjacency List |       0       | Correct Shortest Distances | Correct Shortest Distances |             23.5045 |  Pass  |
| BFS       | `bfs_100000.txt`  |       100000 |    200000 | Unweighted Adjacency List        |       0       | Valid BFS Traversal        | Valid BFS Traversal        |              5.3222 |  Pass  |
| DFS       | `dfs_100000.txt`  |       100000 |    200000 | Unweighted Adjacency List        |       0       | Valid DFS Traversal        | Valid DFS Traversal        |              8.092 |  Pass  |
| SSSP      | `sssp_100000.txt` |       100000 |    200000 | Positive Weighted Adjacency List |       0       | Correct Shortest Distances | Correct Shortest Distances |             30.2236 |  Pass  |

---

## Performance Analysis

Execution time was measured using the C++ `chrono::high_resolution_clock`.

Assuming that the number of vertices (V) <= 100 are considered 'fast inputs', in that case we take the average execution time over 100 runs. Otherwise we take the execution time only for a single run.

Compilation was performed using:

```
g++
```

---

## Time and Space Complexity

| Algorithm                          | Time Complexity      | Space Complexity | Remarks                                                                                                                                                                |
| ---------------------------------- | -------------------- | ---------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| BFS                                | **O(V + E)**         | **O(V)**         | Each vertex and edge is visited at most once during traversal.                                                                                                         |
| DFS                                | **O(V + E)**         | **O(V)**         | Each vertex and edge is processed once. The auxiliary space is due to the recursion stack (or an explicit stack in an iterative implementation) and the visited array. |
| SSSP                               | **O((V + E) log V)** | **O(V + E)**     | Implemented using Dijkstra's algorithm with a priority queue on the CSR graph representation.                                                                          |
| CSR Graph Representation           | **O(V + E)**         | **O(V + E)**     | CSR stores the graph compactly using three arrays: `row_ptr`, `col_idx`, and `values`, making it efficient for graph traversal algorithms.                             |

---

## References

1. Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, and Clifford Stein, *Introduction to Algorithms*, 4th Edition, MIT Press.
2. Robert Sedgewick and Kevin Wayne, *Algorithms*, 4th Edition, Addison-Wesley.
3. C++ Standard Template Library (STL) documentation for `queue`, `priority_queue`, `vector`, and `chrono`.

---
