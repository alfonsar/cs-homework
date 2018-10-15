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
        if(j<len)
        {
            //checking for n
            if(s[i]=='n')
            {
                if(s[j]!='s'&& input.top()!='s')
                {
                    input.push(i);
                }
                else if(s[j]!='s' && input.top()=='s')
                {
                    if(input.size()!=0)
                    {
                        input.pop();
                    }
                }
                else if(s[j]=='s')
                {
                    i+=2;
                }
            }
            //checking for s
            if(s[i]=='s')
            {
                if(s[j]!='n'&& input.top()!='n')
                {
                    input.push(i);
                }
                else if (s[j]!='n' && input.top()=='n')
                {
                    if(input.size()!=0)
                    {
                        input.pop();
                    }
                }
                else if(s[j]=='n')
                {
                    i+=2;
                }
            }
            //checking for w
            if(s[i]=='w')
            {
                if(s[j]!='e'&& input.top()!='e')
                {
                    input.push(i);
                }
                else if (s[j]!='e' && input.top()=='e')
                {
                    if(input.size()!=0)
                    {
                        input.pop();
                    }
                }
                else if(s[j]=='e')
                {
                    i+=2;
                }
            }
            //checking for e
            if(s[i]=='e')
            {
                if(s[j]!='w'&& input.top()!='w')
                {
                    input.push(i);
                }
                else if (s[j]!='w' && input.top()=='w')
                {
                    if(input.size()!=0)
                    {
                        input.pop();
                    }
                }
                else if(s[j]=='w')
                {
                    i+=2;
                }
            }
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