# KNNClassifier
<h2>K Nearest Neighber Classifier </h2>

The code is a from scratch implementation of KNN in C++ programing language.The Algorithm is distributed in a object oriented system.

<h3><u>Input Strucutre</u></h3>

1. The Feature Matrix is a vector of vectors of float (currently) and the input format is given below

<br>

| Feature 0 | Feature 1 | Feature 2 |  .. .. .. | Feature N |
| --------- | --------- | --------- | --------- | --------- |
| Observation 00 | Observation 01 | Observation 02|  .. .. .. | Observation 0N |
| Observation 10 | Observation 11 | Observation 12|  .. .. .. | Observation 1N |
| Observation 20 | Observation 21 | Observation 22|  .. .. .. | Observation 2N |
| : | : | :|  .. .. .. | : |
| Observation M0 | Observation M1 | Observation M2|  .. .. .. | Observation MN |

<br><br>

The equivalent C++ representation would be done by initialising vector of vectors like :-

```c++
std::vector<vector<float> > X = { {Observation 00,Observation 01,Observation 02,Observation 03, .. .. .., Observation 0N}, 
                                  {Observation 10,Observation 11,Observation 12,Observation 13, .. .. .., Observation 1N}, 
                                  {Observation 20,Observation 21,Observation 22,Observation 23, .. .. .., Observation 2N}, 
                                  {:,:,:, .. .. .. ,:},
                                  {Observation M0,Observation M1,Observation M2, .. .. .., Observation Mn}};
                                  
```
<br>

For example a Feature matrix with four features may look like


```c++
std::vector<std::vector<float> > X = { {2,3,4,5}, 
                                  {1,2,3,4}, 
                                  {4,2,3,1}, 
                                  {4,2,1,4}, 
                                  {5,1,3,4}};

```


<br><br>


2. The vector of prediction is a vector of float (currently) and the input format is given below
<br>


| TARGET | 
| --------- |
| Target 1 |
| Target 2 |
| Target 3 | 
| : |
| Target M |

<br><br>

The equivalent C++ representation would be done by initialising vector of float like :-

```c++
std::vector<float> y = {Target 1, Target 2, Target 3, .. .. .. , Target N};
```
<br>

For example a vector of prediction may look like


```c++
std::vector<float> > X = {2,3,4,5}; 


```

<h3><u>Assumptions</u></h3>

This algorithm takes the following assumptions about the data :-

1) The data consists of discrete values , not categorical.
2) The values are of datatype float (Currently)
3) Decision conflict are to be solved by greedy approach. 


<h3><u>Implementation</u></h3>

<h5>Object Creation</h5>
Knn class is called to make an object. The default values are neighbors=1,distance_metric="euclidean", mode="none". Selecting differnet parameters donot effect the program execution (currently)

<h5> Function : apply() </h5>
Input : Feature Matrix and Vector of prediction<br>
Output : None<br>
Working :- The function checks for null values and if the two matrices are comparable i.e The number of observations are same.It then updates its private memebers X and y which now store the Feature Matrix and Vector of prediction respectively<br>

<h5> Function : Classify()</h5>
Input : Test Feature Matrix<br>
Output : None <br>
Working : - Calculates the distance in required distance metric, sorts in the increasing order of their magnitude and then keep the number of neighbors defined during object creation. Performs a decision  of classification on the basis of occurence of each class.The class with highest count is selected. The classified values are stored in vector of float val_pred.

<h5> Function : print_class()</h5>
Input : None<br>
Output : None<br>
Wokring : - After Classify is called the predicted class is stored in vector val_pred. This function performs a pretty print of the values.

<h4>Useful public variables</h4>
 -<b>neighbors : </b> Stores the number of neighbores to consider, can be changed at any moment of compiling.
 -<b>distance_metric :</b> Stores the distnce metric being used , can be changed at any moment of compiling.
 -<b> mode : </b> Mode defines the reaction to an error or warning. Currently supported modes are none and informative.Informative can display extra helful information during a runtime error.Can be changed at any moment of compiling
 -<b>distances : </b> Stores unsorted, ordered distances from the test set to original points.Dynamically changes, should not be changed manually.
 -<b>distances_sorted : </b> Stores sorted, ordered distances from the test set to original points.Dynamically changes, should not be changed manually.
 -<b> n_distances : </b> Stores sorted ordered n distances , where n is the number of neighbors. Dynamically chages, should not be changed manually.
 -<b> pred_values : </b> Stores the predicted values in order. Should be accessed only after applying and classifying. (apply(), classify()).
 -<b> dis_to_y : </b> Stores mapping of distance to its target value. Should only be used for debugging purposes.




