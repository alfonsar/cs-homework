#include <iostream>
#include <ostream>
#include <fstream>
#include "stackint.h"
#include "circular_list_int.h"

void print (StackInt &stack)
{
	while(!stack.empty())
	{
		std::cout<<stack.top()<<std::endl;
		stack.pop();
	}
	return;
}


int main(int argc, char* argv[])
{
	if(argc<2)
	{
		return -1;
	}
	std::ifstream infile;
	infile.open(argv[1]);
	const int OPEN_PAREN=-1;
	const int CLOSED_PAREN=-2;
	const int MULT=-3;
	const int PLUS=-4;
	const int LEFT=-5;
	const int RIGHT=-6;
	std::string s_line;
	while(getline(infile,s_line))
	{
		bool good=false;
		if(s_line.size()==0)
		{
			continue;
		}
		StackInt syntax;
		for(int i=0;i<s_line.size();i++)
		{
			if(s_line[i]=='(')
			{
				syntax.push(OPEN_PAREN);
			}
			if(s_line[i]==')')
			{
				syntax.pop();
				//continue;
			}
			if(syntax.empty())
			{
				good=true;
			}
		}
		//if(good)
		//{	
			StackInt mystack;
			for(int i=0;i<s_line.size();i++)
			{
				if(s_line[i]==' ') continue;
				else if(s_line[i]=='(') mystack.push(OPEN_PAREN);
				//if(s_line[i]==')') mystack.push(CLOSED_PAREN);
				else if(s_line[i]=='*') mystack.push(MULT);
				else if(s_line[i]=='+') mystack.push(PLUS);
				else if(s_line[i]=='<') mystack.push(LEFT);
				else if(s_line[i]=='>') mystack.push(RIGHT);
				else if(s_line[i]==')')
				{
					int n=1;
					int number=0;
					bool begin=false;
					while(mystack.top()!=OPEN_PAREN)
					{
						while(mystack.top()>-1 && !mystack.empty())
						{
							number+=mystack.top()*n;
							n*=10;
							begin=true;
							mystack.pop();
							std::cout<<number<<std::endl;
						}
						
						if(mystack.top()==LEFT || mystack.top()==RIGHT )
						{
							if (!begin) 
							{
								good=false;
								return -3;
							}
							while(mystack.top()==LEFT)
							{
								mystack.pop();
								number*=2;
							}
							while(mystack.top()==RIGHT)
							{
								mystack.pop();
								number/=2;
							}
						}
						StackInt calc;
						calc.push(number);
						if(mystack.top()==MULT || mystack.top()==PLUS)
						{
							calc.push(mystack.top());
							mystack.pop();
						}
						int oper_m=0;
						int oper_p=0;
						mystack.pop(); //pop open paren
						int topper=0;
						while(!calc.empty())
						{
							if(calc.size()==1)
							{
								good=false;
							}
							topper=calc.top();
							calc.pop();
							if(calc.top()==MULT)
							{
								oper_m++;
								//check to see if two operands are together
								if(oper_p==0)
								{
									calc.pop();
									topper*=calc.top();
								}
								else {good=false;}
								
							}
							if(calc.top()==PLUS)
							{
								oper_p++;
								//check to see if two operands are together
								if(oper_m==0)
								{
									calc.pop();
									topper+=calc.top();
								}
								else {good=false;}
							}
							
							//calc.pop();
						}
						mystack.push(topper);
					}	
				}
				else
				{
					int num=s_line[i]-'0';
					mystack.push(num);
				}
			}
		std::cout<<mystack.top()<<std::endl;
		//}	
		if(!good)
		{
			std::cout<<"Malformed"<<std::endl;
		}
	}
}











