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


