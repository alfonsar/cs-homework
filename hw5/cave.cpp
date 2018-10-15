#include <iostream>
#include <stack>
int main()
{
    std::string s;
    bool rolled=false;
    std::stack<char>input;
    std::cout<<"Enter a string"<<std::endl;
    std::cin>>s;
    for(int i=0; i<s.length();i++)
    {
        if(s[i]=='s'||s[i]=='n'||s[i]=='e'||s[i]=='w')
        {}
        else 
        {
            std::cout<<"Invalid"<<std::endl;
            break;
        }

    }
    if(s.length()%2!=0)
    {
        rolled=false;
    }
    int len=s.length();
    for(int i=0; i<len;i++)
    {
        int j=i+1;
        if(j<len && (s[i]=='n' && s[j]=='s') || (s[i]=='s' && s[j]=='n') ||(s[i]=='w' && s[j]=='e')||(s[i]=='e' && s[j]==w))
        {
        	i++;
        }
        else 
        {
        	
        }

    }
    if(input.size()==0&& s.length()>1)
    {
        rolled=true;
    }
    if(rolled)
    {
        std::cout<<"Rolled up"<<std::endl;
    }
    else 
    {
        std::cout<<"Not rolled"<<std::endl;
    }
    return 0;
}