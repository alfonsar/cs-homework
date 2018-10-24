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

template<class T, class Comparator>
void merging(std::vector<T>&myArray, std::vector<std::pair<int,int> >&places, Comparator comp)
{
	int beg= places[0].first;
	int len=places.size();
	int end=places[len-1].second;

	std::vector<T>tmp;

	while(len!=0)
	{
		T smallest=myArray[places[0].first];
		int smallPlace=0;
		for(int m=0; m<len;m++)
		{
			if(!comp(smallest,myArray[places[m].first]))
			{
				smallest=myArray[places[m].first];
				smallPlace=m;
			}
		}
		tmp.push_back(myArray[places[smallPlace].first]);
		places[smallPlace].first++;
		if(places[smallPlace].first>places[smallPlace].second)
		{
			places.erase(places.begin()+smallPlace);
		}
	}
	for(int i=0; i<end+1-beg;i++)
	{
		myArray[i+beg]=tmp[i];
	}
}

template<class T, class Comparator>
//selection sort
void selecSort(std::vector<T>& myArray, int beg, int end, Comparator comp)
{
	int smallestPlace=0;
	for(int j=beg; j<end-1; j++)
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
void many(std::vector<T>& myArray, int k, int beg, int end, Comparator comp)
{
	if(beg<end)
	{
		std::vector<std::pair<int,int> >placeHolder;
		int median=(beg-end+1)/k;
		for(int j=0; j<k;j++)
		{
			if(j==(k-1))
			{
				std::pair<int,int> last_one(placeHolder.back().second+1,end);
				placeHolder.push_back(last_one);
			}
			else if(j==0)
			{
				std::pair<int,int> first_one(beg, beg+median-1);
				placeHolder.push_back(first_one);
			}
			else
			{
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
void mergeSort(std::vector<T>& myArray, int k, Comparator comp)
{
	int beg=0;
	int len=myArray.size();
	int end=len-1;
	many(myArray,k,beg,end, comp);
}