#include <vector>
#include <string>
#include<iostream>
#include "Tile.h"
#include "Player.h"
#include "Bag.h"
#include "Dictionary.h"
#include "Player.h"
#include "Move.h"

PlaceMove::PlaceMove (size_t x, size_t y, bool horizontal, std::string tileString, Player * p){
	initialx=x;
	initialy=y;
	place_word=tileString;
	horiz=horizontal;
	player=p;
	take=player->takeTiles(tileString,1);
}
void PlaceMove::correct(Board& board,Dictionary& dictionary)
{
	while(!(player->hasTiles(place_word,1))
	{
		std::cout<<"Error: You do not have the necessary tiles"<<std::endl;
		anotherAttempt();
	}
	bool middle=false;
	if(board.firstMove())
	{
		std::pair<size_t,size_t>center;
		center=std::make_pair(initialx,initialy);
		while(horiz && (initialx<))

		/*
		size_t middle_x=board.getsx();
		size_t middle_y=board.getsy();

		while (!middle)
		{
			if(horiz)
			{
				if(initialx+ place_word.size()>=middle_x)
				{
					middle=true;
				}
			}
			else
			{
				if(initialy+place_word.size()>=middle_y)
				{
					middle=true;
				}
			}
			std::cout<<"Error: Middle space must be occupied. Enter a valid move"<<std::endl;
			anotherAttempt();
		}
		*/
	}
	//now we check for adjacency 
	bool touching=false;
	size_t len=place_word.size();
	while(!touching)
	{
		if(horiz)
		{	
			if(initialx-1>0 && board.getSquare(initialx-1,initialy)->isOccupied())
			{
				touching=true;
			}
			if(initialx+len+1 <= board.getColumns() && board.getSquare(initialx+len+1, initialy)->isOccupied())
			{
				touching=true;
			}
			for(size_t i=initialx; i<initialx+len;i++)
			{
				if(board.getSquare(i, initialy+1)->isOccupied() || board.getSquare(i, initialy-1)->isOccupied())
				{
					touching=true;
				}
			}
		}	
		else 
		{
			if(initialy-1>0 && board.getSquare(initialx,initialy-1)->isOccupied())
			{
				touching=true;
			}
			if(initialy+len+1 <= board.getRows() && board.getSquare(initialx, initialy+len+1)->isOccupied())
			{
				touching=true;
			}
			for(size_t i=initialy; i<initialy+len;i++)
			{
				if(board.getSquare(initialy+1, i)->isOccupied() || board.getSquare(initialy-1, i)->isOccupied())
				{
					touching=true;
				}
			}	
		}
	}
	if(!touching)
	{
		std::cout<<"Error: Tiles are not touching"<<std::endl;
		anotherAttempt();
	}
	//checks for out of bound moves
	bool inbound=false;	
	while(!inbound)
	{
		if(horiz){
			if(initialx>0 && initialx<=board.getColumns())
			{
				if(initialx+place_word.size()<=board.getColumns())
				{
					inbound=true;
				}
			}
		}
		else
		{
			if(initialy>0 &&initialy<=board.getColumns())
			{
				if(initialy+place_word.size()<=board.getRows())
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
	/*
	while(dictionary.isLegalWord(place_word)!=1)
	{
		std::cout<<"Error: Word not legal. Enter a valid move"<<std::endl;
		anotherAttempt();
	}
	*/
	//check for overlapping
	bool ontop=true;
	while(ontop)
	{
		if(horiz)
		{
			for(size_t i=initialx;i<initialx+place_word.size();i++)
			{
				if(board.getSquare(initialx,i)->isOccupied())
				{
					std::cout<<"Error: Overlapping another word."<<std::endl;
					anotherAttempt();
					continue;
				}
			}
		}
		else if (!horiz)
		{
			for(size_t i=initialx;i<initialx+place_word.size();i++)
			{
				if(board.getSquare(i,initialx)->isOccupied())
				{
					std::cout<<"Error: Overlapping another word"<<std::endl;
					anotherAttempt();
					continue;
				}
			}
		}
		ontop=false;
	}
	bool isaWord=formingWords(gameboard,dictionary);
	if(!isaWord)
	{
		std::cout<<"Error: Formed words are not in dictionary. Enter a valid move"<<std::endl;
		anotherAttempt();
	}
}
bool PlaceMove:: formingWords(Board& board, Dictionary& dictionary, std::string move)
{
	//vector to add words too
	//will check if all the words move_word makes are legal
	std::vector<std::string>check_words;
	//if place is horizontal
	if(horiz)
	{	
		size_t c_col=initialx;
		size_t c_row=initialy;
		size_t length=move.size();
		size_t index=0;
		while(index<length && board.getSquare(initialx,initialy)->isOccupied())
		{
			std::string possible_word="";
			//if the top of a letter is occupied, it will keep going up till the top of the word
			while(c_row-1>0 && board.getSquare(c_col-1,c_row-1)->isOccupied())
			{
				c_row--;
			}
			//now we will go all the way down the word 
			while(c_row<board.getRows() && board.getSquare(c_col,c_row+1)->isOccupied())
			{
				//adding to word
				possible_word+=board.getSquare(c_col,c_row)->getLetter();
				c_row++;
				//if the next spot is empty but where the placemove string is going to be placed
				//then add from the player's hand
				if(c_row+1==initialy)
				{
					possible_word+=move[index];
					index++;
					continue;
				}
			}
			if(possible_word!="")
			{
				check_words.push_back(possible_word);
			}
		}
		size_t h_col=initialx;
		size_t h_row=initialy;
		size_t tileIndex=0;
		std::string h_word="";
		//go all the way to the left of the horizontal word
		while(h_col>0 && board.getSquare(h_col-1,c_row)->isOccupied)
		{
			h_col--;
		}
		while(tileIndex<length)
		{
			if(board.getSquare(h_col,h_row)->isOccupied())
			{
				h_word+=board.getSquare(h_col,h_row)->getLetter();
				h_col++;
			}
			else
			{
				h_word+=move[tileIndex];
				tileIndex++;
				h_col++;
			}
		}
		while(h_col<board.getColumns() && board.getSquare(h_col,h_row)->isOccupied())
		{
			h_word+=board.getSquare(h_col,h_row)->getLetter();

		}
		if(h_word!="")
		{
			check_words.push_back(h_word);
		}
		
	}
	if(!horiz)
	{	
		size_t c_col=initialx;
		size_t c_row=initialy;
		size_t length=move.size();
		size_t index=0;
		while(index<length && board.getSquare(initialx,initialy)->isOccupied())
		{
			std::string possible_word="";
			//if the top of a letter is occupied, it will keep going up till the top of the word
			while(c_col>0 && board.getSquare(c_col-1,c_row)->isOccupied())
			{
				c_col--;
			}
			while(c_col<board.getColumns() && board.getSquare(c_col+1,c_row)->isOccupied())
			{
				possible_word+=board.getSquare(c_col,c_row)->getLetter();
				c_col++;
				if(c_col+1==initialx)
				{
					possible_word+=move[index];
					index++;
					continue;
				}
			}
			if(possible_word!="")
			{
				check_words.push_back(possible_word);
			}
		}
		size_t h_col=initialx;
		size_t h_row=initialy;
		size_t tileIndex=0;
		std::string h_word="";
		//go all the way to the top of the vertical word
		while(h_row>0 && board.getSquare(h_col,c_row-1)->isOccupied)
		{
			h_row--;
		}
		while(tileIndex<length)
		{
			if(board.getSquare(h_col,h_row)->isOccupied())
			{
				h_word+=board.getSquare(h_col,h_row)->getLetter();
				h_row++;
			}
			else
			{
				h_word+=move[tileIndex];
				tileIndex++;
				h_row++;
			}
		}
		while(h_row<board.getRows() && board.getSquare(h_col,h_row)->isOccupied())
		{
			h_word+=board.getSquare(h_col,h_row)->getLetter();

		}
		if(h_word!="")
		{
			check_words.push_back(h_word);
		}
		
	}

}
std::vector<Tile*> const & PlaceMove::tileVector() const
{

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
		horiz=false;
	}
	std::cin>>initialx>>initialy>>place_word;
}
