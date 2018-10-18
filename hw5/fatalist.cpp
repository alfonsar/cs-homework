#include<vector>
#include<utility>
#include<iostream>

bool sortinrev(const std::pair<int,int> &a,const std::pair<int,int> &b) 
{ 
    return (a.first > b.first); 
} 
bool sort2inrev(const std:: pair<int,int> &a, const std::pair<int,int>&b)
{
    return (a.second>b.second);
}
bool FatalistHypothesis(std::vector<std::pair<int,int> > grades)
{
    sort(grades.begin(),grades.end(),sortinrev);
    bool asc=true;
   // std::vector<std::pair<int,int> > ::iterator it;
    int len=grades.size();
    for(int i=0; i<len;i++)
    {
        if(i+1<len)
        {
            if(grades[i].second<grades[i+1].second)
            {
                asc=false;
            }
        }
    }
    bool asc2=true;
    sort(grades.begin(),grades.end(),sort2inrev);
    for(int i=0; i<len;i++)
    {
        if(i+1<len)
        {
            if(grades[i].first<grades[i+1].first)
            {
                asc2=false;
            }
        }
    }
    if(asc && asc2)
    {
        return 1;
    }
    return 0;
}



int main()
{
    /*
    int arr1[]={3,2,1,4};
    int arr2[]={1,2,6,7};
   std::vector<std::pair<int,int> > num;
    for(int i=0;i<4;i++)
    {
        num.push_back(std::make_pair(arr1[i],arr2[i]));
    }
    sort(num.begin(),num.end(),sortinrev);
    int len=num.size();
    for(int i=0;i<len;i++)
    {
        std::cout<<"Pair:"<<i<<" "<<num[i].first<<" "<<num[i].second<<std::endl;
    }
    */
return 0;
}
