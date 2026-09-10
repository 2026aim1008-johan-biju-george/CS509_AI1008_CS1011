## Gradient Descent

- Gradient Descent is an iterative optimization algorithm that repeatedly updates a current value in the direction that decreases an objective function. For this assignment, every student must use the same generic one-variable polynomial representation so that higher-degree functions can be tested without requiring symbolic expression parsing or advanced optimization theory.

* `f(x) = c0 + c1*x + c2*x^2 + ... + cd*x^d`
* `f'(x) = c1 + 2*c2*x + 3*c3*x^2 + ... + d*cd*x^(d-1)`
* `x_new = x - learning_rate * f'(x)`

- The degree d and coefficients c0, c1, ..., cd are read from the input file. The same implementation must work for all required polynomial degrees; do not hard-code a separate function for each test case.
- Required tests use polynomial degrees 2, 4, 6, 8 and 10. The supplied functions are convex with a single global minimum, so students are not required to study or prove convexity.
- The input file also supplies the initial x value, learning rate, tolerance and maximum number of iterations. Stop when `|f'(x)| <= tolerance`, or when the maximum number of iterations has been reached.

Real-Life Use Cases of Gradient Descent
- Training machine-learning models by minimizing a loss or error function.
Parameter estimation and curve fitting.
- Engineering design optimization where a differentiable cost function must be minimized.
Resource-allocation and numerical optimization problems with differentiable objectives.

## Maxflow-Mincut
- The Maxflow problem asks for the largest amount of flow that can be sent from a source vertex s to a sink vertex t in a directed graph without exceeding edge capacities. The corresponding minimum s-t cut partitions the vertices into two sets so that s and t are separated and the total capacity of edges crossing from the source side to the sink side is minimum.
- Each directed edge has a non-negative capacity. For the required tests, use positive integer capacities.
- The maximum-flow value must be equal to the minimum-cut capacity.
- After computing maximum flow, the minimum cut can be obtained from the final residual graph by finding all vertices still reachable from the source.
- Any correct maximum-flow implementation may be used. Dinic's algorithm is recommended because the required graph sizes are larger; slower implementations may become impractical on the largest tests.

### Dinic's Algorithm
- Initialize residual graph G as given graph.
- Do BFS of G to construct a level graph (or assign levels to vertices) and also check if more flow is possible.
- If more flow is not possible, then return
- Send multiple flows in G using level graph until **blocking flow** is reached. 
- Here using level graph means, in every flow, levels of path nodes should be 0, 1, 2...(in order) from s to t.

**Note:** A flow is Blocking Flow if no more flow can be sent using level graph, i.e., no more s-t path exists such that path vertices have current levels 0, 1, 2... in order.

Real-Life Use Cases of Maxflow-Mincut
- Finding the maximum traffic, data, water, or material that can move through a capacity-limited network.
- Communication-network bandwidth and bottleneck analysis.
- Transportation and logistics planning.
- Image segmentation and computer-vision problems that can be represented as graph cuts.
Assignment, matching, and scheduling problems that can be reduced to flow networks.

## Gradient Descent Results

| Test File | Degree | Initial x | Learning Rate | Tolerance | Max Iter. | Actual x | Actual f(x) | Iter. / Time | Status |
| :--- | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| gd_01.txt | 2 | 0 | 0.10 | 1e-6 | 5,000 | 3.00000 | 2.45e-13 | 71 / 0 ms | Pass |
| gd_02.txt | 4 | 2 | 0.02 | 1e-6 | 10,000 |  2.3791e-007 | 1.13202e-013 | 181 / 0 ms | Pass |
| gd_03.txt | 6 | 2 | 0.02 | 1e-6 | 20,000 | 4.83545e-007 | 2.33816e-013 | 350 / 0 ms | Pass |
| gd_04.txt | 8 | 2 | 0.01 | 1e-8 | 50,000 | 4.97473e-009 | 2.4748e-017 | 949 / 0 ms | Pass |
| gd_05.txt | 10 | 2 | 0.005 | 1e-10 | 100,000 | 4.96359e-011 | 2.46373e-021 | 2,365 / 0 ms | Pass |

## Maxflow-Mincut Results

| File | V | E | Source | Sink | Expected Flow | Actual Flow | Cut Capacity | Time (ms) | Status |
| :--- | :--- | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| maxflow_10.txt | 10 | 20 | 0 | 9  | 25 | 25 | 25 | 0.071 | Pass |
| maxflow_100.txt | 100 | 200 | 0 | 99  | 30 | 30 | 30 | 0.3605 | Pass |
| maxflow_1000.txt | 1000 | 2000  | 0 | 999  | 15 | 15 | 15 | 3.4992 | Pass |
| maxflow_10000.txt | 10000  | 20000  | 0 | 9999  | 65 | 65 | 65 | 26.7296 | Pass |


