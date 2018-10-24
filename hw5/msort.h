#include <algorithm>
#include <vector>
#include <string>
#include <cstdlib>
#include <iostream>
#include <vector>
//#include "functor.h"
/*
template<class T, class Comparator>
void merging(std::vector<T>&myArray, std::vector<std::pair<int,int> >&places, Comparator comp);
template<class T, class Comparator>
void many(std::vector<T>& myArray, int k, int beg, int end, Comparator comp);
template<class T, class Comparator>
void sSort(std::vector<T>& myArray, int beg, int end, Comparator comp);
*/

//the function used to merge the partitions 
template<class T, class Comparator>
void merging(std::vector<T>&myArray, std::vector<std::pair<int,int> >&places, Comparator comp)
{
	//
	int beg= places[0].first;
	//variable to store length of vecot
	int len=places.size();
	int end=places[len-1].second;

	std::vector<T>tmp;

	//while the list is not empty
	while(places.size()!=0)
	{
		T smallest=myArray[places[0].first];
		int smallPlace=0;
		for(int m=1; m<len;m++)
		{
			//comparing the smallest 
			if(!comp(smallest,myArray[places[m].first]))
			{
				smallest=myArray[places[m].first];
				smallPlace=m;
			}
		}
		//temporary vector will hold the 
		tmp.push_back(myArray[places[smallPlace].first]);
		places[smallPlace].first++;
		if(places[smallPlace].first>places[smallPlace].second)
		{
			//erases the smallPlace index from the vector
			places.erase(places.begin()+smallPlace);
		}
	}
	//will store the elements from the temporary vector into our myArray vector
	for(int i=0; i<end+1-beg;i++)
	{
		myArray[i+beg]=tmp[i];
	}
}

template<class T, class Comparator>
void many(std::vector<T>& myArray, int k, int beg, int end, Comparator comp)
{
	if(beg<end)
	{
		//vector of pairs
		std::vector<std::pair<int,int> >placeHolder;
		//grab the median but instead of splitting in two ways, we do k ways
		int median=(beg-end+1)/k;
		for(int j=0; j<k;j++)
		{
			//if j is last value
			if(j==(k-1))
			{
				//from C++ reference, the .back() function returns a reference to the
				//last element
				std::pair<int,int> last_one(placeHolder.back().second+1,end);
				//push the pair into the placeHolder vector
				placeHolder.push_back(last_one);
			}
			//if j is first value
			else if(j==0)
			{
				std::pair<int,int> first_one(beg, beg+median-1);
				placeHolder.push_back(first_one);
			}
			else
			{
				//from C++ reference, the .back() function returns a reference to the
				//last element
				std::pair<int,int> other(placeHolder.back().second+1, placeHolder.back().second+median);
				placeHolder.push_back(other);
			}
		}
		int len=placeHolder.size();
		for(int j=0; j<len;j++)
		{
			if(placeHolder[j].second-placeHolder[j].first+1<k)
			{
				selecSort(myArray, placeHolder[j].first, placeHolder[j].second,comp);
			}
			else
			{
				many(myArray,k,placeHolder[j].first, placeHolder[j].second,comp);
			}
			merging(myArray,placeHolder,comp);
		}
	}
}
template<class T, class Comparator>
//selection sort
//basic implementation of selection sort
void selecSort(std::vector<T>& myArray, int beg, int end, Comparator comp)
{
	int smallestPlace=0;
	for(int j=beg; j<end+1; j++)
	{
		smallestPlace=j;
		for(int k=j+1; j<end+1; j++)
		{
			if(comp(myArray[k],myArray[smallestPlace]))
			{
				smallestPlace=k;
			}
		}
		std::swap(myArray[smallestPlace],myArray[j]);
	}

}

template<class T, class Comparator>
void mergeSort(std::vector<T>& myArray, int k, Comparator comp)
{
	//establish the beginning as 0
	int beg=0;
	//have len store size
	int len=myArray.size();
	//establish the end of the vector
	int end=len-1;
	many(myArray,k,beg,end, comp);
}