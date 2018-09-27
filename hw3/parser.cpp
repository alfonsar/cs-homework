#include <iostream>
#include <ostream>
#include <fstream>
#include <sstream>
#include "stackint.h"
#include <string>
#include "circular_list_int.h"


int main(int argc, char* argv[])
{
	if(argc<2){ return -1;}
	//variables set to constance
	const int OPEN_PAREN=-1;
	//const int CLOSED_PAREN=-2;
	const int MULT=-3;
	const int PLUS=-4;
	const int LEFT=-5;
	const int RIGHT=-6;
	std::ifstream infile(argv[1]);
	std::string s_line;
	while(getline(infile,s_line))
	{

		//the following is to take out the many spaces that
		//could exists 
		std::string &sent=s_line;
		char toomany;
		std::stringstream ll(sent);
		sent="";
		while(ll>>toomany)
		{
			sent+=toomany;
		}
		//checks for the case where there are only blank lines
		int spacer=0;
		for(int i=0;i<s_line.size();i++)
		{
			if(!isspace(s_line[i]))
			{
				spacer++;;
			}
		}
		if(spacer==0)
		{
			continue;
		}
		bool bad=false;
		int parents=0;
		StackInt mystack;
		std::stringstream ss(s_line);
		char buffer;
		while(ss>>buffer)
		{
			if(buffer=='(')
			{
				//if we find an open parentheses, then we push it
				mystack.push(OPEN_PAREN);
				//this variable is used to check for balanced parantheses
				parents++;
			}
			else if(buffer=='*')
			{
				//according to piazza
				//the peek function helps my looking at next character
				//in stringstream without taking it out
				//SO HELPFUL
				char next=ss.peek();
				//checks to see if there are two operators */+ next to each other
				if(next=='+')
				{
					bad=true;
					break;
				}
				else if(next=='*')
				{
					bad=true;
					break;
				}
				//if no error, we push the *
				mystack.push(MULT);
			}
			else if(buffer=='+')
			{
				//according to piazza
				//the peek function helps my looking at next character
				//in stringstream without taking it out
				char next=ss.peek();
				//check for possible errors
				if(next=='+')
				{
					bad=true;
					break;
				}
				if(next=='*')
				{
					bad=true;
					break;
				}
				//push plus if no error found
				mystack.push(PLUS);
			}
			else if(buffer=='>')
			{
				if(mystack.top()>-1 && mystack.top()<10 &&mystack.size()!=0)
				{
					bad=true;
					break;
				}
				mystack.push(RIGHT);
			}
			else if(buffer=='<')
			{
				if(mystack.top()>-1 && mystack.top()<10 &&mystack.size()!=0)
				{
					bad=true;
					break;
				}
				mystack.push(LEFT);
			}
			else if(buffer==')')
			{
				//if we find a closed parantheses
				parents--;
				//checks to see if there is a an operator before closed paren
				if(mystack.top()<0)
				{
					bad=true;
					break;
				}
				//variable to store number
				int topper=mystack.top();
				mystack.pop();
				//now we check to see if we need to mult,add,left, or right the number (topper)
				if(mystack.top()==MULT)
				{
					//once we know it is multiplication, we can pop
					mystack.pop();
					while(mystack.top()!=OPEN_PAREN)
					{
						//will run through the expression in parantheses
						if(mystack.top()>=0)
						{
							//if its a integer, then it will do the multiplication
							topper*=mystack.top();
							mystack.pop();
						}
						//if there are two operators next to each other, then bad
						else if(mystack.top()==PLUS)
						{
							bad=true;
							break;
						}
						else if(mystack.top()==MULT)
						{
							mystack.pop();
							if(mystack.top()==OPEN_PAREN)
							{
								bad=true;
								break;
							}
						}
					}
					//now that we are done, we can pop the open parantheses
					if(mystack.top()==OPEN_PAREN) {mystack.pop();}
				}
				//just like we did for multiplication, we do for addition
				else if(mystack.top()==PLUS)
				{
					mystack.pop();
					while(mystack.top()!=OPEN_PAREN)
					{
						if(mystack.top()>=0)
						{
							//do addition here
							topper+=mystack.top();
							mystack.pop();
						}
						else if(mystack.top()==MULT)
						{
							bad=true;
							break;
						}
						else if(mystack.top()==PLUS)
						{
							mystack.pop();
							if(mystack.top()==OPEN_PAREN)
							{
								bad=true;
								break;
							}
						}
					}
					if(mystack.top()==OPEN_PAREN){mystack.pop();}
				}
				//if its not an operator the bad
				else
				{
					bad=true;
					break;
				}
				//here we do the math with the left and right operators
				//since there could be more than one operator, then i use a while loop
				while(mystack.top()==LEFT || mystack.top()==RIGHT)
				{
					//performs the math accordingly
					if(mystack.top()==LEFT)
					{
						mystack.pop();
						topper*=2;
					}
					else if(mystack.top()==RIGHT)
					{
						mystack.pop();
						topper/=2;
					}
				}
				//push the converted number to stack
				mystack.push(topper);
			}
			//now we convert the numbers from chars to actual ints
			else if(buffer<='9' && buffer>='0')
			{
				//again, peek allows us to look at the next character in string stream
				char next=ss.peek();
				//convert chars to ints by subtracting '0'
				int convert=buffer-'0';
				//this while loop only executes if the number is greater than 9
				while(next<='9'&&next>='0')
				{
					//adjusts the numbers accordingly
					//since we are only looking at individual chars, if a number is 245 for example,
					//it reads it in as 2 4 5 so this will combine the numbers to actually appear
					//as 245 
					convert*=10;
					convert+=next-'0';
					//will create a temp in order to move along and "peek" at the next function
					char get_rid;
					ss>>get_rid;
					next=ss.peek();
				}
				//math involving the shift left and right operators
				while(mystack.top()==RIGHT || mystack.top()==LEFT)
				{
					if(mystack.top()==LEFT)
					{
						mystack.pop();
						convert*=2;
					}
					else if(mystack.top()==RIGHT)
					{
						mystack.pop();
						convert/=2;
					}
				}
				//finally push
				mystack.push(convert);
			}
			//for cases where there are letters after
			//an expression, this turns it malform
			else 
			{
				bad=true;
			}

		}
		if(mystack.size()!=1)
		{
			bad=true;
		}
		//checks for balanced parentheses
		if(parents!=0)
		{
			bad=true;
		}
		//the following are for cases when there
		//is an operation or '(', ')' left in stack
		if(mystack.top()<0)
		{
			bad=true;
		}
		if(bad)
		{
			std::cout<<"Malformed"<<std::endl;
			continue;
		}
		std::cout<<mystack.top()<<std::endl;
	}
	return 0;
}

