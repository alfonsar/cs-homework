#include <iosteam>
#include <ostream>
#include <fstream>
#include "stackint.h"
#include "circular_list_int.h"


int main(int argc, char* argv[])
{
	if(argc<3)
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
	string s_line;
	while(getline(infile,s_line))
	{
		bool good=false;
		//if emptty, we move on
	
		if(s_line.size()==0)
		{
			continue;
		}
		
		Stack syntax;
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
			if(syntax.size()==0)
			{
				good=true;
			}
		}
			if(good)
			{
				Stack mystack;
				for(int i=0;i<s_line.size();i++)
				{
					if(s_line[i]==' ')
					{
						continue;
					}
					if(s_line[i]=='(')
					{

					}
					if(s_line[i]=='*')
					{
						mystack.push(MULT);
					}
					if(s_line[i]=='+')
					{
						mystack.push(PLUS);
					}
					if(s_line[i]=='<')
					{
						mystack.push(LEFT);
					}
					if(s_line[i])=='>');
					{
						mystack.push(RIGHT);
					}
					if(s_line[i]>-1)
					{
						mystack.push(s_line);
					}	
				}
				int n=1;
				int numbers=0;
				bool begin=false;
				Stack calc;
				while(mystack.top()!=OPEN_PAREN)
				{
					while(mystack.top()>-1 && mystack.size()!=0)
					{
						number+=mystack.top()*n;
						n*=10;
						//begin=true;
						mystack.pop();

					}
					if(mystack.top()==LEFT || mystack.top()==RIGHT )
					{
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
					calc.push(number);
					
					if(mystack.top()==MULT || mystack.top()==PLUS)
					{
						calc.push(mystack.top());
						mystack.pop();
					}
				}
				mystack.pop(); //pop open paren
				while(!calc.empty())
				{
					int topper=calc.top();
					calc.pop();
					if(calc.top()==MULT)
					{
						calc.pop();
						topper*=calc.top();
						
					}
					if(calc.top()==ADD)
					{
						calc.pop();
						topper+=calc.top();
					}
					mystack.push(topper)
					calc.pop();
				}
			}


		
	}
}
