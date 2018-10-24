#include<vector>
#include<utility>
#include<algorithm>
#include<iostream>

bool sortinrev(const std::pair<int,int> &m,const std::pair<int,int> &n) 
{ 
    return (m.first > n.first); 
} 
bool sort2inrev(const std:: pair<int,int> &o, const std::pair<int,int>&p)
{
    return (o.second>p.second);
}
bool FatalistHypothesis(std::vector<std::pair<int,int> > grades)
{
    //sort in descending order by 104 grades
    sort(grades.begin(),grades.end(),sortinrev);
    //check to see if the 170 grades are also in descending
    bool des=true;
    int len=grades.size();
    for(int i=0; i<len;i++)
    {
        if(i+1<len)
        {
            //since it is sorted in descending order by 104 grades
            //if grades[i].second <grades[i+1].second, the hypothesis is wrong
            if(grades[i].second<grades[i+1].second)
            {
                des=false;
            }
        }
    }
    //check to see if 104 grades are also in descending order
    bool des2=true;
    //we now sort 170 grades in descending order
    sort(grades.begin(),grades.end(),sort2inrev);
    for(int i=0; i<len;i++)
    {
        if(i+1<len)
        {
            //since it is sorted in descedning order by 170 grades
            //if grades[i].first< grades[i+1].first the hypothesis is wrong
            if(grades[i].first<grades[i+1].first)
            {
                des2=false;
            }
        }
    }
    //if both are true, then hypothesis is true
    if(des && des2)
    {
        return 1;
    }
    //otherwise return false
    return 0;
}



