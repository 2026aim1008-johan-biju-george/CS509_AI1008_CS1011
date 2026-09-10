# Brief explanation of the algorithms

## K-Means Clustering (Reference: https://cs229.stanford.edu/summer2023/cs229-notes7a.pdf)
K-Means Clustering partitions N data points in D-dimensional space into K clusters, so that each point belongs to the cluster whose centroid (mean) is closest, minimizing the within-cluster sum of squared distances (WCSS).

- Initialize K centroids (the first K input points, in input order, are recommended for reproducibility).
- Assignment step: assign every point to the nearest centroid using Euclidean distance.
Update step: recompute each centroid as the mean of the points currently assigned to it.
- Repeat the assignment and update steps until no point changes cluster (or the centroid shift is below the tolerance), or the maximum number of iterations is reached.
- If a cluster becomes empty during an update, keep its previous centroid unchanged for that iteration.

Real-Life Use Cases of K-Means Clustering:
- Customer and market segmentation.
- Image compression and color quantization.
- Document and text clustering.
- Anomaly/outlier detection and unsupervised pattern discovery.
Most popular unsupervised ML algorithm: Healthcare and medical data analysis, Speech/audio processing, Feature engineering / preprocessing (Vector quantization, Data summarization, Model compression), Attention/token routing in efficient transformers, etc.

## FastMap
- FastMap is a heuristic algorithm that maps N objects, described only by a pairwise distance function, into a k-dimensional Euclidean space so that Euclidean distances in the new space approximate the original distances. It does this without ever forming the full distance matrix explicitly beyond what is provided as input, and without eigen-decomposition.
- For each of the k target dimensions, choose a pair of 'pivot' objects that are approximately the farthest apart, using a fast heuristic (pick a random object, find the object farthest from it, then find the object farthest from that one; repeat once or twice).
- Project every object onto the line joining the two pivots using the law of cosines to obtain its coordinate for the current dimension.
- Update ('deflate') the remaining pairwise distances to remove the contribution already captured by this dimension before computing the next dimension.
- Repeat until k coordinates have been produced for every object.

Real-Life Use Cases of FastMap:
- Dimensionality reduction for visualization of high-dimensional or non-vector data.
- Indexing and speeding up similarity search in multimedia databases.
- Preprocessing for clustering or nearest-neighbour search when only distances (not coordinates) are known.
- Bioinformatics: visualizing sequences or structures compared only via distance/similarity scores.
- Heuristic search / pathfinding in AI


## 1. K-Means Clustering Results 

| File | N | D | K | Max Iter. | Actual Iter. | WCSS | Time (ms) | Status |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| `km_01.txt` | 100 | 2 | 3 | 300 | 6 | 57552.14 | 0.966200 | Pass |
| `km_02.txt` | 1,000 | 2 | 5 | 300 | 16 | 349244.84 | 7.012000 | Pass |
| `km_03.txt` | 10,000 | 5 | 8 | 300 | 120 | 21033573.20 | 1274.618600 | Pass |
| `km_04.txt` | 100,000 | 5 | 10 | 300 | 223 | 189290911.02 | 31157.748700 | Pass |

---

## 2. FastMap Results 

| File           |      N | Target k | Pivots (per dim)     |        Time (ms) | Status |
| -------------- | -----: | -------: | -------------------- |  ---------: | ------ |
| `fm_10.txt`    |     10 |        2 | (3,0), (2,7)         |   0.0476  | Pass   |
| `fm_100.txt`   |    100 |        2 | (61,98), (71,35)     |    2.4905  | Pass   |
| `fm_1000.txt`  |  1,000 |        2 | (590,983), (543,938) |   79.9251  | Pass   |
| `fm_10000.txt` | 10,000 |        2 | -                    |          - | Fail   |

Pivot selection uses a farthest-point heuristic. Starting from an initial object, the object farthest from it is selected as the first pivot, followed by the object farthest from that pivot as the second pivot.


