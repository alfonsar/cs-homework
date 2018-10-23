#include <iostream>
#include <stack>
int main()
{
    //variable to read in string
    std::string s;
    //bool to check for rolled
    bool rolled=false;
    //stack used to check for circle scenario
    std::stack<char>input;
    //prompt user for string
    std::cout<<"Enter a string"<<std::endl;
    std::cin>>s;
    int len=s.length();
    //will check to make sure string is valid
    for(int i=0; i<len;i++)
    {
        //if these letters are entered, do nothin
        if(s[i]=='s'||s[i]=='n'||s[i]=='e'||s[i]=='w')
        {}
        else if(s[i]==' ')
        {
            std::cout<<"Invalid"<<std::endl;
            return -1;
        }
        //if other letters are entered, then string is invalid
        else 
        {
            std::cout<<"Invalid"<<std::endl;
            return -1;       
         }

    }
    //if an odd number of characters in the string is given, then 
    //then it will not be rolled up
    if(s.length()%2!=0)
    {
        rolled=false;
    }
    
    for(int i=0; i<len;i++)
    {
        int j=i+1;
        //if the current letter is complementary to i+1 (j) then we will jump ahead and ignore them
        if(j<len &&( (s[i]=='n' && s[j]=='s') || (s[i]=='s' && s[j]=='n') ||(s[i]=='w' && s[j]=='e')||(s[i]=='e' && s[j]=='w')))
        {
        	i++;
        }
        else 
        {
        	//while the stack is not empty
            if(!input.empty())
            {
                //if we look at i and check i+1 and it is not complementary, we look at the stack
                //and check to see if the top is its complementary
                if( (s[i]=='n' && input.top()=='s') || (s[i]=='s' && input.top()=='n') || (s[i]=='e' && input.top()=='w') || (s[i]=='w' && input.top()=='e'))
                {
                    input.pop();
                }
            }
            //if none of the above cases are true, we push onto stack
            else
            {
                input.push(s[i]);
            }
        }

    }
    //if the stack is empty and the string was greater than one character
    //roll is true
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