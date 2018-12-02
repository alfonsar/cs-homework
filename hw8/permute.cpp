#include <iostream>
#include <string>
#include<algorithm>
#include <queue>
#include <bits/stdc++.h>
#include <vector>
using namespace std;


//comparator given to us in skeleton code 
//of functor.h in hw5
struct lengthStrComp{
  bool operator()(const std::string& lhs, const std::string& rhs)
  { // Compares strings by size;
    return (lhs.size() < rhs.size());
   }         
};
//function used to permute. The purpose of this function is to 
//permutate all of letters that will be in the hand along with the letters
//already on the board. This is to see all possible combinations
//then when we will run it by the trie to check if the combo is a word
//and if it is, then it will be added to a priority queue where 
//it will be prioritized in a priority queue
void permutations(string input, string curr, priority_queue<string,vector<string>,lengthStrComp>& setter)
{
	int len=input.length();
	string temp="";
	if(input.empty())
	{
		return;
	}
	int j=0;	
	while(j<len)
	{
		string add=curr+input[j];
		setter.push(add);
		bool found=false;
		for(int k=0; k<len;k++)
		{
			
			if(input[k]==input[j] && found==false) 
			{
				found=true;
				
			}
			else if(input[k]!=input[j])
			{
				temp+=input[k];
			}
			else if(input[k]==input[j] && found==true)
			{
				temp+=input[k];
			}

		}
		permutations(temp,add,setter);
		temp="";
		j++;
	}
	return;
}
   
int main() 
{ 
    string str = "apple"; 
    priority_queue<string,vector<string>,lengthStrComp> setup;
    permutations(str,"", setup); 
    return 0; 
} 