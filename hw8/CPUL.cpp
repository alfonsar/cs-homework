#include <fstream>
#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <queue>

#include "Board.h"
#include "Bag.h"
#include "Dictionary.h"
#include "ConsolePrinter.h"
#include "Player.h"
#include "ConfigFile.h"
#include "Exceptions.h"
#include "rang.h"

using namespace std;
/*
void AllCombos(priority_queue<string>& result, string input, int k)
{
	string append="";
	int len=input.length();
	permuteAll(&result, append, input, len);
}
priority_queue<string> permuteAll(priority_queue<string>*result, string append, string input, int k)
{
	if(k==0)
	{
		result->push(append);
		return result;
	}
	int len=input.size();
	for(int i=0; i<len;i++)
	{
		string temp=permuteAll(result,append+input[i],input,k-1);
	}
	return result;
}

void sort(priority_queue<string>*result)
{
	int len=result.size();
	for(int i=1; i<len;i++)
	{
		string temp = result[i];
		int j=i-1;
		while(j>=0 && temp.length()< s[j].length())
		{
			s[j+1]=s[j];
			j--;
		}
		s[j+1]=temp;
	}
}
*/
string pusher(vector<string>* result, string append, string input, int k);
void AllCombos(vector<string>& result, string input, int k){
    string append="";
    pusher(&result,append,input,k);
	
}
string pusher(vector<string>* result,string append, string input, int k)
{
    if(k==0)
        
    {
        result->push_back(append);
        return "";
    }
    for(int i=0; i<input.size(); i++)
    {
        string temp = pusher(result,append+input[i], input, k-1);
    }
    return "";
}

void subString(string s, int n)
{
	for(int i=0; i<n;i++)
	{
		for(int len=1; len<=n-i;len++)
		{
			cout<<s.substr(i,len)<<endl;
		}
	}
}
int main()
{
	string s="abcd";
	subString(s,s.length());
	cout<<"all combos"<<endl;
	cout<<endl;
	cout<<endl;
	
	for(int i=0;i<result.size();i++)
	{
		cout<<result[i]<<endl;
	}
	return 0;
}