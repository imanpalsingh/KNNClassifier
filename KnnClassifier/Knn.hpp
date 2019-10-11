/*
 *
 * Description : - Header file for definition of Knn Class
 * Author :  - Imanpal Singh <imanpalsingh@gmail.com>
 * Date created : - 01-10-2019
 * Last modified : - 11-10-2019
 *
*/


#ifndef KNN_HPP   
#define KNN_HPP


/*
 *
 * Class Name : - Knn
 * Description : - Class contains are the nesseary memebers required to perform KNN, Working is given in the documentation
 *
 */
class Knn
{
	
private:
	
	//Error detection variables
	bool isapplied = false;	
	bool ispred = false;

	//Vector to hold Feature Matrix and Vector of prediction
	std::vector<std::vector<float> > X;
	std::vector<float> y;

	//Utility functions
	void determine_class();
	void sort_distances();
	void euc_dis(std::vector<std::vector<float> > points);

	//Ilegal operation detection functions
	bool check_null(std::vector<std::vector<float> >);
	bool check_train_test_equal(std::vector<std::vector<float> >);
	bool check_X_y_equal(std::vector<std::vector<float> >, std::vector<float>);	
	bool check_n_less_dis();
	
		
public :

	//Algorithimic variables/vectors
	
	
	int neighbors;
	std::string distance_metric;
	std::string mode;
	std::vector<std::vector<float> > distances;
	std::vector<std::vector<float> > distances_sorted;
	std::vector<std::vector<float> > n_distances;
	std::vector<float> pred_values;
	std::vector<int> indexes;
	std::multimap<float,float> dis_to_y;
	
	//Constructors overloaded
	Knn();
	Knn(int,std::string,std::string);

	//Algorithmic initializers
	void apply(std::vector<std::vector<float> >, std::vector<float>);
	void classify(std::vector<std::vector<float> >);

	//Informative functions
	void print_class();
	void stat();

};

#endif
