/*
 *
 * Description : - Machine Learning algorithm K Nearest Neighbor Classifier c++ implementation
 * Author :  - Imanpal Singh <imanpalsingh@gmail.com>
 * Date created : - 01-10-2019
 * Last modified : - 11-10-2019
 *
*/




#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<map>
#include"Knn.h"




/*
 *
 * Function Name: - Knn
 * Input : None
 * Return : None
 * Logic :  Constructor to load default values to the required variables
 *
*/
Knn::Knn()

{
	neighbors = 1;
	distance_metric = "eucledian";
	mode="none";

}

/*
 *
 * Function Name: - Knn
 * Input : None
 * Return : None
 * Logic :  Constructor overloaded to load user defined vales to the required variables
 *
*/
Knn::Knn(int n_neighbors,std::string metric,std::string mode_)
{
	neighbors = n_neighbors;
	distance_metric = metric;
	mode = mode_;
}


/*
 *
 * Function Name: - apply
 * Input : X_ - > Feature matrix from user, y_-> Vector of prediction from user
 * Return : None
 * Logic :  Applying error detection methods such as if null values are present or 
 *					if dimensions are equal and storing the Feature matrix and vector of predicton
 *
*/
void Knn::apply(std::vector<std::vector<float> > X_, std::vector<float> y_)
{
	if(!check_null(X_))
		return;
	
	if(!check_X_y_equal(X_,y_))
		return;
	
	X = X_;
	y = y_;
	
	isapplied = true;
	stat();
}
/*
 *
 * Function Name: - classify
 * Input : X_ - > Test Feature matrix from user on whom to apply classification of,
 * Return : None
 * Logic :  Applying error detection methods such as if Knn is applied first, and if train and test sets are of equal dimensions
 *					Calculating the required distance metrics and determing the class they belongs to.
 *
*/

void Knn::classify(std::vector<std::vector<float> >X_)
{
	if(!isapplied)
	{
		stat();
		return;
	}

	if(!check_train_test_equal(X_))
		return;


	euc_dis(X_);
	determine_class();
	


}

/*
 *
 * Function Name: - euc_dis
 * Input : points - > set of points(vector of vectors) from where to calculate eucledian distance to.
 * Return : None
 * Logic :  Calculating eucledian distance and assigning the distances vector with the respective distancs.
 *
*/

void Knn::euc_dis(std::vector<std::vector<float> > points)
{
	int distance;
	std::vector<float> distance_hold;
	
	for(int i=0; i<points.size(); i++)
	
	{
				distance_hold.clear();
				
				for(int j=0; j<X.size(); j++)

					{  
						distance = 0;
						
						for(int k=0; k<points[0].size(); k++)
						
						{
						
							distance+= (points[i][k]-X[j][k])*(points[i][k]-X[j][k]);
						
						}

					distance_hold.push_back(distance);

					}

					distances.push_back(distance_hold);

	}

}

/*
 *
 * Function Name: - determine_class
 * Input : None
 * Return : None
 * Logic :  Based on the distances calculated, determining the class taking the neighbors into consideration.
 *
*/

void Knn::determine_class()
{
	if(!check_n_less_dis())
	{
		std::cout<<"<In Knn::determine_class()> WARNING: Neighbors cannot be more than number of data points. (Expect Irrelevent results).\n";
		
		if(mode=="informative")
			std::cout<<"(Informative) Try n_neighbors lesser than "<<X.size()*X[0].size()<<".\n";
	}


	for(int i =0; i<distances.size(); i++)
	
	{
		for(int j=0; j<distances[0].size(); j++)
	
		{
			dis_to_y.insert(std::pair<float,float>(distances[i][j],y[j]));
	
		}
		
	}
	
	sort_distances();
	
 	std::vector<float> n_distances_hold;
	
	for(int i=0; i<distances_sorted.size();i++)
	
	{
		n_distances_hold.clear();
		int n=0;
	
		for(int j = 0; j<distances_sorted[0].size(); j++)
	
		{
			
			if(n==neighbors)
				break;
			
			n_distances_hold.push_back(distances_sorted[i][j]);
			n+=1;

		}
	
		n_distances.push_back(n_distances_hold);
	
	}
	

	std::vector<int> oc;
 	std::vector<std::vector<int> > oc_container;
 	auto y_max= *std::max_element(std::begin(y), std::end(y));
 	
 	for(int i=0; i<n_distances.size(); i++)
 	
 	{	
 		oc.clear();
 	
 		for(int j=0;j<=y_max;j++)
 			oc.push_back(0);
 	
 		oc_container.push_back(oc);
 	
 	}

 	for(int i=0; i<n_distances.size(); i++)
 	
 	{
 		for(int j=0; j<n_distances[0].size(); j++)
 	
 		{
 			oc_container[i][dis_to_y.find(n_distances[i][j])->second]+=1;
 		}
 	}

	for(int i=0;i<oc_container.size();i++)
 	
 	{
 		pred_values.push_back(*std::max_element(std::begin(oc_container[i]), std::end( oc_container[i])));
 		ispred = true;

 	}
 	
 	std::cout<<"CLASSIFIED : KNN.\n";
 }
 
	
/*
 *
 * Function Name: - sort_distances
 * Input : None
 * Return : None
 * Logic :  The distances obtained are sorted.
 *
*/
 	
 void Knn::sort_distances()
{
	distances_sorted  = distances;
	
	for(int i=0;i<distances_sorted.size(); i++)
		std::sort(distances_sorted[i].begin(), distances_sorted[i].end());
}

/*
 *
 * Function Name: - print_class
 * Input : None
 * Return : None
 * Logic :  Error checking;if Knn is applied and if classify is called successfullt. Prints the last predicted value(s).
 *
*/
void Knn::print_class()
{
	if(!isapplied)
	{
		stat();
		return;
	}

	if(!ispred)
	{
		std::cout<<"<In Knn::print_class()> ERROR: KNN is applied but no Classify operation has been done yet.Use classify().\n";
		
		if(mode=="informative")
			std::cout<<"(informative)After calling apply() pass the test set to clssify() to predict values.\n";
	}

	std::cout<<"The last predicted value(s) is/are :\n\n";
	int index=1;
	
	for(auto i:pred_values)
		std::cout<<index++<<") "<<i<< "\n";

	std::cout<<"\n";
}

/*
 *
 * Function Name: - check_train_test_equal
 * Input : X_ -> Vector of vectors to compare with original Feature matrix(vector of vectors)
 * Return : True - > if comparable, False -> If not.
 * Logic :  The number of features in each entry should be same as the Feature matrix. and number of entries may differ.
 *
*/

bool Knn::check_train_test_equal(std::vector<std::vector<float> >X_)
{

	for(int i=0;i<X_.size();i++)
	{
		if(X[i].size() != X_[i].size())
		{
			std::cout<<"<In Knn::check_train_test_equal> Error: Test Feature matrix should have same features as the Feature matrix that was used to apply KNN.\n";
			
			if(mode =="informative")
			{
				std::cout<<"[Informative] Column "<<i+1<<" of Test Feature matrix has elements : ";
				
				for(int j=0; j<X_[i].size();j++)
				
				{
					std::cout<<X_[i][j]<<" ";
				}

				std::cout<<".The number of features/elements  '"<<X_[i].size()<<"' is not equal to number of featues/elements in the Feature matrix that was used to apply KNN i.e '"<<X[i].size()<<"'.\n";
			}

			return false;

		}
	}

	return true;
}

/*
 *
 * Function Name: - check_null
 * Input : X_ -> Vector of vectors to check if missing values are present
 * Return : True - > if missing values not present, False -> If present.
 * Logic :  The number of features in each entry should be same.
 *
*/

bool Knn::check_null(std::vector<std::vector<float> >X_)
{
	std::vector<int> noe;
	
	for(int i=0; i<X_.size(); i++)
	
	{
	
		noe.push_back(X_[i].size());
	
	}

	float sum=0;
	
	for(int i=0; i<noe.size();i++)
	
	{
	
		sum+=noe[i];
	
	}
	

	if( (sum/noe.size()) != noe[0])
	{
		std::cout<<"<In Knn::checknull()> ERROR: Missing values found in Feature Matrix.\n";
	
		if(mode =="informative")
		{
			std::cout<<"[Informative] The number of features/elements in each row of Feature matrix is not equal.\n";
		}
	
		return false;
	}

	return true;
}

/*
 *
 * Function Name: - check_X_y_equal
 * Input : X_ -> Feature Matrix, y_ -> Vector of prediction.
 * Return : True - > if dimensions are equal, False -> If not.
 * Logic :  The number of entries/observations should be same;
 *
*/

bool Knn::check_X_y_equal(std::vector<std::vector<float> > X_, std::vector<float> y_)
{
	if( (X_.size())!=y_.size())
	{
		std::cout<<"<In Knn::apply()> ERROR: Feature matrix and Vector of prediction should be of same size.\n";
		
		if(mode == "informative")
		{
			std::cout<<"[Informative] The number of rows in Feature matrix X '"<<X_.size()<<"' is not equal to number of rows in Vector of prediction '"<<y_.size()<<"'.\n";
		}
		
		return false;
	}

	return true;
}

/*
 *
 * Function Name: - check_n_less_dis
 * Input : None
 * Return : True - > if neighbors are more than observations
 * Logic :  The number of entries/observations should be more than neighbors;
 *
*/

bool Knn::check_n_less_dis()
{
	if (neighbors > distances[0].size())
		return false;

	return true;
}

/*
 *
 * Function Name: - :stat
 * Input : None
 * Return : None 
 * Logic :  Showing the status of the algorihtm, applied or not.
 *
*/
void Knn::stat()
{
	if(isapplied)
		std::cout<<"APPLIED: KNN -> neighbors["<<neighbors<<"], distance_metric["<<distance_metric<<"], mode["<<mode<<"].\n";
	
	else
		std::cout<<"<In Knn::stat()> ERROR: KNN needs to be applied first. (use apply()).\n";
}








int main()
{
	//Refer Documentation for examples
	



}
