
#ifndef MOVE_H_
#define MOVE_H_
#include <vector>
#include <string>
#include "Tile.h"
#include "Player.h"
#include "Bag.h"
#include "Dictionary.h"

PlaceMove::PlaceMove (size_t x, size_t y, bool horizontal, std::string tileString, Player * p){
	initialx=x;
	initialy=y;
	tileString=place_word;
	horiz=horizontal;
}

void PlaceMove::correct(Board& board,Dictionary& dictionary)
{
	bool middle=false;
	if(board.firstMove())
	{
		size_t middle_x=board.getsx();
		size_t middle_y=board.getsy();

		while (!middle)
		{
			if(horiz)
			{
				if(initialx+tileString.size()>=middle_x)
				{
					middle=true;
				}
			}
			else
			{
				if(initialy+tileString.size()>=middle_y)
				{
					middle=true;
				}
			}
			std::cout<<"Error: Middle space must be occupied. Enter a valid move"<<std::endl;
			anotherAttempt();
		}
	}
	bool inbound=false;	
	while(!inbound)
	{
		if(horiz){
			if(initialx>0 && initial<=board.getColumns())
			{
				if(initialx+tileString.size()<=board.getColumns())
				{
					inbound=true;
				}
			}
		}
		else
		{
			if(initialy>0 &&initialy<=board.getColumns())
			{
				if(initialy+tileString.size()<=board.getRows())
				{
					inbound=true;
				}
			}
		}
	
		if(!inbound)
		{
			std::cout<<"Error: Out of bounds. Enter a valid move"<<std::endl;
			anotherAttempt();
		}
	}
	while(dictionary.isLegalWord(tileString)!=1)
	{
		std::cout<<"Error: Word not legal. Enter a valid move"<<std::endl;
		anotherAttempt();
	}
	bool isaWord=formingWords;
	if(!isaWord)
	{
		std::cout<<"Error: Formed words are not in dictionary. Enter a valid move"<<std::endl;
		anotherAttempt();
	}
}
bool PlaceMove:: formingWords(Board& board,Dictionary& dictionary)
{
	vector<string>check_words;
	bool notWord=false;
	size_t col_curr=initialx+1;
	size_t len=1;
	for(size_t i=initialx; i+word.size();i++)
	{
		while(board[i][col_curr].isOccupied())
		{
			len++;
			col_curr++;
		}
		col_curr=initialx-1;
		while(board[i][col_curr].isOccupied())
		{
			len++;
			col_curr--;
		}
		if(len>1)
		{
			std::string hold;
			for(int k=col_curr;k<col_curr+len;k++)
			{
				hold+=board[i][k].getLetter();
				check_words.push_back(hold);
			}
		}
	}
	//checks for words 
	size_t row_curr=initialy+1;
	size_t len1=1;
	for(size_t j=initialy;j+word.size();j++)
	{
		while(board[row_curr][j].isOccupied())
		{
			len1++;
			row_curr++
		}
		row_curr=initialy-1;
		while(board[row_curr][j].isOccupied())
		{
			len1++;
			row_curr--;
		}
		if(len1>1)
		{
			std::string temp;
			for(int m=row_curr;m<row_curr+len;m++)
			{
				temp+=board[j][m].getLetter();
				check_words.push_back(temp);
			}
		}
	}

	vector<string>::iterator it;
	for(it=check_words.begin(); it!=check_words.end();++it)
	{
		if(dictionary.isLegalWord(*it)==1)
		{
			notWord=true;
		}
	}
	return notWord
}
void PlaceMove::anotherAttempt()
{
	char direction;
	std::cin>>direction;
	if(direction=='-')
	{
		horiz=true;
	}
	else
	{
		horiz=false
	}
	std::cin>>initialx>>initialy>>tileString;
}
