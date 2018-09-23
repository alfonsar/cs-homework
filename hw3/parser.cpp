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
			if(good)
			{
				Stack mystack;
				for(int i=0;i<s_line.size();i++)
				{
					if(s_line[i]==' ')
					{
						continue;
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
				while(mystack.size()!=0)
				{
					int top1=mystack.top();
					mystack.pop();
					int top2=mystack.top();
					mystack.pop();
					if(top1<0)
					{
						top1=top2;
						top2=mystack.top();
					}
				}
				
			}


		}
	}
}
