#include <vector>
#include <string>
#include<iostream>
#include<iterator>
#include "Tile.h"
#include "Player.h"
#include "Bag.h"
#include "Dictionary.h"
#include "Board.h"
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
	/* Executes this move, whichever type it is.
	   This may throw exceptions; students: it's up to you to
	   decide (and document) what exactly it throws*/


void PlaceMove::execute(Board & board, Bag & bag, Dictionary & dictionary)
{
	size_t this_score=0;
	//make a vector of pairs where the pair will contain the placeMove string and the score associated with that word
	std::vector<std::pair<std::string, unsigned int>> moveResults= board.getPlaceMoveResults(*this);
	board.executePlaceMove(*this);
	std::string this_word=word();
	std::vector<std::pair<std::string, unsigned int>>::iterator it;
	std::cout<<"Your move has made the following words: ";
	for(it=moveResults.begin();it!=moveResults.end();++it)
	{
		std::cout<<(*it).first<<"  ";
		this_score+=(*it).second;
	}
	//if you use all the letters in your hand, you get a bonus
	if(this_word.length()==player->getMax())
	{
		player->score+=50;
	}
	player->score+=this_score;
	std::cout<<"From this move, you have earned "<<this_score<< " points"<<std::endl;
	std::cout<<"After this move, your total score is "<<player->score<<std::endl;
	//now that we erase the tiles from hand
	player->erasefromHand(this_word);
	//now we grab new tiles from the bag 
	std::vector<Tile*>brandNew=bag.drawTiles(this_word.size()); 
	
    for(std::vector<Tile*>::iterator it=brandNew.begin();it!=brandNew.end();++it)
    {
        //we insert them back into our hand
		player->hand.insert(*it);
    }

}

void PlaceMove::correct(Board& board,Dictionary& dictionary)
{
	while(!(player->hasTiles(place_word,1)))
	{
		std::cout<<"Error: You do not have the necessary tiles"<<std::endl;
		anotherAttempt();
	}
	//checks to make sure that first move places a tile on board starting position
	if(board.firstMove())
	{
		size_t boardInitialX=board.getsx();
		size_t boardInitialY=board.getsy();
		if(horiz)
		{
			while((boardInitialX<initialx)||(boardInitialX>initialx+place_word.length()))
			{
				std::cout<<"Error: You must place word on starting square"<<std::endl;
				anotherAttempt();
			}
		}
		if(!horiz)
		{
			while((boardInitialY<initialy)||(boardInitialY>initialy+place_word.length()))
			{
				std::cout<<"Error: You must place word on starting square"<<std::endl;
				anotherAttempt();			
			}
		}
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
		if(horiz)
		{
			if(initialx>0 && initialx<=board.getColumns()&& initialy>0 && initialy<board.getRows())
			{
				if(initialx+place_word.size()<=board.getColumns())
				{
					inbound=true;
				}
			}
		}
		else
		{
			if(initialy>0 &&initialy<=board.getColumns()&& initialx>0 && initialx<board.getColumns())
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
	//check for overlap
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
	bool isaWord=formingWords(board,dictionary,place_word);
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
		while(index<length)
		{
			std::string possible_word="";
			//if the top of a letter is occupied, it will keep going up till the top of the word
			while(c_row-1>0 && board.getSquare(c_col,c_row-1)->isOccupied())
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
				if(!(board.getSquare(c_col,c_row+1)->isOccupied()))
				{
					possible_word+=move[index];
					index++;
					c_row++;
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
		while(h_col-1>0 && board.getSquare(h_col-1,c_row)->isOccupied)
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
			//if the square is not occupied, then we grab the corresponding index of the 
			//move string
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
			while(c_col-1>0 && board.getSquare(c_col-1,c_row)->isOccupied())
			{
				c_col--;
			}
			//move all the way to the right of word (end)
			while(c_col<board.getColumns() && board.getSquare(c_col+1,c_row)->isOccupied())
			{
				possible_word+=board.getSquare(c_col,c_row)->getLetter();
				c_col++;
				//since in this case it will be unoccupied since it is where 
				//place move will be placed if valid, then we use the letter from
				//corresponding index
				if(c_col+1==initialx)
				{
					possible_word+=move[index];
					c_col++;
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
		while(h_row-1>0 && board.getSquare(h_col,c_row-1)->isOccupied)
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
			//if not occupied, we will use corresponding index of tileString
			else
			{
				h_word+=move[tileIndex];
				tileIndex++;
				h_row++;
			}
		}
		//if we run out of tiles, there could still be letters that appear after our
		//last used tile so we check for that 
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
 return take;
}
//when a bad attempt is made, we prompt the user to enter
//a valid move
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
