#include <fstream>
#include <string>
#include <iostream>
#include <iomanip>
#include<vector>
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

void createInitBoard(std::string input, rows, columns)
{
	std::ifstream infile(input);
	for(int i=0; i<rows;i++)
	{
		for(int j=0; j<columns*3;j+=3)
		{
			char set;
			infile>>set;
			if(set=='.')
			{
				continue;
			}
			else if((set>='a' && set<='z') || (set>='A' && set<='Z'))
			{
				//make tile
				int score;
				infile>>score;
				//now place score 
				Tile add =Tile(set,score);
				getSquare(i,j%3)->placeTile(add);				
			}
		}
	}
}
*/
int main()
{
	
	return 0;
}

vector<pair<size_t,size_t> > startingPos(Board& board,size_t rows, size_t cols)
{
	vector<pair<size_t,size_t> > spotChecker;
	for(size_t i=1;i<=rows;i++)
	{
		for(size_t j=1;j<=cols;j++)
		{
			if(i<2 && j!=cols)
			{
				if(!(board.getSquare(j,i)->isOccupied()) )
				{
					if(board.getSquare(j+1,i)->isOccupied()) 
					{
						std::pair<size_t,size_t> coor(j+1,i);
						spotChecker.push_back(coor);
					}
					if(board.getSquare(j,i+1)->isOccupied())
					{
						std::pair<size_t,size_t> coor(j,i+1);
						spotChecker.push_back(coor);
					}
				}
			}
			else if(j<2 && i!=rows)
			{
				if(!(board.getSquare(j,i)->isOccupied()))
				{
					if(board.getSquare(j,i+1)->isOccupied())
					{
						std::pair<size_t,size_t>coor(j,i+1);
						spotChecker.push_back(coor);
					}
					if(board.getSquare(j+1,i)->isOccupied())
					{
						std::pair<size_t,size_t>coor(j+1,i);
						spotChecker.push_back(coor);
					}
				}
			}
			else if(i==rows && j!=cols)
			{
				if(!(board.getSquare(j,i)->isOccupied()))
				{
					if(board.getSquare(j,i-1)->isOccupied())
					{
						std::pair<size_t,size_t>coor(j,i-1);
						spotChecker.push_back(coor);
					}
					if(board.getSquare(j+1,i)->isOccupied())
					{
						std::pair<size_t,size_t>coor(j+1,i);
						spotChecker.push_back(coor);
					}
				}
			}
			else if(j==cols && i!=rows)
			{
				if(!board.getSquare(j,i)->isOccupied())
				{
					if(board.getSquare(j-1,i)->isOccupied())
					{
						std::pair<size_t,size_t>coor(j-1,i);
						spotChecker.push_back(coor);
					}
					if(board.getSquare(j,i+1)->isOccupied())
					{
						std::pair<size_t,size_t>coor(j,i+1);
						spotChecker.push_back(coor);
					}
				}
			}
			else
			{
				if(!board.getSquare(j,i)->isOccupied())
				{
					if(board.getSquare(j,i+1)->isOccupied())
					{
						std::pair<size_t,size_t>coor(j,i+1);
						spotChecker.push_back(coor);
					}
					if(board.getSquare(j,i-1)->isOccupied())
					{
						std::pair<size_t,size_t>coor(j,i-1);
						spotChecker.push_back(coor);
					}
					if(board.getSquare(j+1,i)->isOccupied())
					{
						std::pair<size_t,size_t>coor(j+1,i);
						spotChecker.push_back(coor);
					}
					if(board.getSquare(j-1,i)->isOccupied())
					{
						std::pair<size_t,size_t>coor(j+1,i);
						spotChecker.push_back(coor);
					}
				}
			}
			
		}
	}
	return spotChecker;
}