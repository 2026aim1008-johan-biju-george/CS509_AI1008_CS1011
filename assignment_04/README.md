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


