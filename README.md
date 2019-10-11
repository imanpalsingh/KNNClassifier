# KNNClassifier
<h2>K Nearest Neighber Classifier </h2>

The code is a from scratch implementation of KNN in C++ programing language.The Algorithm is distributed in a object oriented system.

<h3><u>Implementation</u></h3>

1. The Feature Matrix is a vector of vectors of float (currently) and the input format is given below


| Feature 0 | Feature 1 | Feature 2 |  .. .. .. | Feature N |
| --------- | --------- | --------- | --------- | --------- |
| Observation 00 | Observation 01 | Observation 02|  .. .. .. | Observation 0N |
| Observation 10 | Observation 11 | Observation 12|  .. .. .. | Observation 1N |
| Observation 20 | Observation 21 | Observation 22|  .. .. .. | Observation 2N |
| : | : | :|  .. .. .. | : |
| Observation M0 | Observation M1 | Observation M2|  .. .. .. | Observation MN |

The equivalent C++ representation would be done by initialising vector of vectors like :-

```c++
std::vector<vector<float> > X = { {Observation 00,Observation 01,Observation 02,Observation 03, .. .. .., Observation 0N}, 
                                  {Observation 10,Observation 11,Observation 12,Observation 13, .. .. .., Observation 1N}, 
                                  {Observation 20,Observation 21,Observation 22,Observation 23, .. .. .., Observation 2N}, 
                                  {:,:,:, .. .. .. ,:},
                                  {Observation M0,Observation M1,Observation M2, .. .. .., Observation Mn}};
                                  
```

For example
```c++
std::vector<vector<float> > X = { {2,3,4,5}, 
                                  {1,2,3,4}, 
                                  {4,2,3,1}, 
                                  {4,2,1,4}, 
                                  {5,1,3,4}};

```

