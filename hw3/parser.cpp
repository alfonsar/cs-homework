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
	const int CLOSED_PAREN=-2;
	const int MULT=-3;
	const int PLUS=-4;
	const int LEFT=-5;
	const int RIGHT=-6;
	std::ifstream infile(argv[1]);
	std::string s_line;
	while(getline(infile,s_line))
	{
		int size=s_line.size();
		bool spacer=false;
		
		for(int i=0;i<size;i++)
		{
			if(!isspace(s_line[i]))
			{
				spacer=true;
			}
		}
		if(!spacer)
		{
			continue;
		}

		std::string &sent=s_line;
		char toomany;
		std::stringstream ll(sent);
		sent="";
		while(ll>>toomany)
		{
			sent+=toomany;
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
				mystack.push(OPEN_PAREN);
				parents++;
			}
			else if(buffer=='*')
			{
				char next=ss.peek();
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
				mystack.push(MULT);
			}
			else if(buffer=='+')
			{
				char next=ss.peek();
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
				parents--;
				if(mystack.top()<0)
				{
					bad=true;
					break;
				}
				int topper=mystack.top();
				mystack.pop();
				if(mystack.top()==PLUS)
				{
					mystack.pop();
					while(mystack.top()!=OPEN_PAREN)
					{
						if(mystack.top()>=0)
						{
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
					else if(mystack.empty())
					{
						bad=true;
						break;
					}
				}
				else if(mystack.top()==MULT)
				{
					mystack.pop();
					while(mystack.top()!=OPEN_PAREN)
					{
						if(mystack.top()>=0)
						{
							topper*=mystack.top();
							mystack.pop();
						}
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
					if(mystack.top()==OPEN_PAREN) {mystack.pop();}
				}
				else
				{
					bad=true;
					break;
				}
				while(mystack.top()==LEFT || mystack.top()==RIGHT)
				{
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
				mystack.push(topper);
			}
			else if(buffer<='9' && buffer>='0')
			{
				char next=ss.peek();
				int convert=buffer-'0';
				while(next<='9'&&next>='0')
				{
					convert*=10;
					convert+=next-'0';
					char get_rid;
					ss>>get_rid;
					next=ss.peek();
				}
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
				mystack.push(convert);
			}
			//for jonathan's case where there are letters after
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
		if(parents!=0)
		{
			bad=true;
		}
		//the following are for cases when there
		//is an operation or '(', ')' left in stack
		if(mystack.top()==CLOSED_PAREN)
		{
			bad=true;
		}
		if(mystack.top()==OPEN_PAREN)
		{
			bad=true;
		}
		if(mystack.top()==MULT)
		{
			bad=true;
		}
		if(mystack.top()==PLUS)
		{
			bad=true;
		}
		if(mystack.top()==LEFT)
		{
			bad=true;
		}
		if(mystack.top()==RIGHT)
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

