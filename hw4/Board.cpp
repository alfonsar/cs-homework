#include <string>
#include <set>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Tile.h"
#include "Square.h"
#include "Move.h"
#include "Board.h"
#include "Dictionary.h"
using namespace std;
Board::Board (std::string board_file_namey){
	ifstream infile;
	infile.open(board_file_namey);
	infile>>rows>>columns>>sx>>sy;
	
	for(size_t i=0; i<rows;i++){
		for(size_t j=0; j<columns;j++){
			char current;
			infile>>current;
			int Lmult=1;
			int Wmult=1;
			bool onit;
			if(current=='2'){Lmult=2;}
			if(current=='3'){Lmult=3;}
			if(current=='d'){Wmult=2;}
			if(current=='t'){Wmult=3;}
			if(i==sx&&j==sy){onit=1;}
			else{onit=0;}
			boardgame[i][j]= new Square (Lmult,Wmult,onit);
		}
	}
}
Board:: ~Board()
{
	for(size_t i=0; i<sx;i++)
	{
		for(size_t j=0;j<sy;j++)
		{
			delete boardgame[i][j];
		}
	}
	//delete gameboard[][];
}

/* Returns a pointer to the Square object representing the
   (y,x) position of the board. Indexing starts at 1 here.
   This is needed only to display the board. */
Square* Board:: getSquare (size_t x, size_t y) const
{
	return boardgame[x-1][y-1];
}
bool Board::firstMove(){
	if(boardgame[sx][sy]->isOccupied()==0){return true;}
	return false;
}
size_t Board::getRows() const{
	return rows;
}

/* Returns the number of columns of the board.*/
size_t Board::getColumns() const{
	return columns;
}
//get function for tile string initial x (columns)
size_t Board::getsx()const
{
	return sx;
}
//get function for tile string initial y(rows)
size_t Board::getsy() const
{
	return sy;
}
/* returns a vector of all words that would be formed by executing the
	given move. The first element of the pair is a string containing the word
	formed, and the second element is the score that that word earns
	(with all multipliers, but not the 50-point bonus for all letters).

       Words returned are all in uppercase.

	   The last entry of the vector is always the "main" word formed
	   in the direction chosen by the user; the others could be in arbitrary
	   order. (This is helpful for backtracking search.)

	   This function does not check that the words formed are actually in the dictionary.
	   The words returned from this function must be checked against the dictionary to
	   determine if the move is legal.	*/
std::vector<std::pair<std::string, unsigned int>> Board::getPlaceMoveResults(const PlaceMove &m) const
{
	std::vector<std::pair<std::string, unsigned int>> contain_words;
	bool isHoriz=m.isHoriz();
	if(isHoriz)
	{	
		size_t c_col=m.getX();
		size_t c_row=m.getY();
		std::string move_word=m.word();
		size_t length=move_word.length();
		size_t score=0;
		size_t index=0;
		size_t lmult=1;
		size_t wmult=1;
		std::vector<Tile*> deck=m.getterPlayer()->takeTiles(move_word,true);
		while(index<length)
		{
			std::string concatenate="";
			//if the top of a letter is occupied, it will keep going up till the top of the word
			while((c_row-1)>0 && getSquare(c_col,c_row-1)->isOccupied())
			{
				c_row--;
			}
			//now we will go all the way down the word 
			while(c_row<getRows() && getSquare(c_col,c_row+1)->isOccupied())
			{
				//adding to the string
				concatenate+=getSquare(c_col,c_row)->getLetter();
				score+=getSquare(c_col,c_row)->getScore();
				c_row++;
				//if the next spot is empty but where the placemove string is going to be placed
				//then add from the player's hand
				if(!(getSquare(c_col,c_row+1)->isOccupied()))
				{
					concatenate+=move_word[index];
					lmult=getSquare(c_col, c_row+1)->getLMult();
					score+= lmult*getSquare(c_col+1,c_row+1)->getScore();
					wmult=wmult*getSquare(c_col,c_row+1)->getWMult();
					c_row++;
					continue;
				}
			}
			if(concatenate!="")
			{
				score+=wmult;
				std::pair<std::string, unsigned int> both;
				both=std::make_pair(concatenate,score);
				contain_words.push_back(both);
			}
			index++;
		}
		size_t h_col=m.getX();
		size_t h_row=m.getY();
		size_t tileIndex=0;
		std::string h_word="";
		//go all the way to the left of the horizontal word
		while(h_col-1>0 && getSquare(h_col-1,c_row)->isOccupied)
		{
			h_col--;
		}
		while(tileIndex<length)
		{
			if(getSquare(h_col,h_row)->isOccupied())
			{
				h_word+=getSquare(h_col,h_row)->getLetter();
				score+=getSquare(c_col,c_row)->getScore();
				h_col++;
			}
			//if the square is not occupied, then we grab the corresponding index of the 
			//move string
			else
			{
				h_word+=move_word[tileIndex];
				score+=lmult*(hand[tileIndex]->getPoints());
				tileIndex++;
				h_col++;
			}
		}
		//if we run out of tiles, there could still be letters that appear after our
		//last used tile so we check for that 
		while(h_col<getColumns() && getSquare(h_col,h_row)->isOccupied())
		{
			h_word+=getSquare(h_col,h_row)->getLetter();
			score+=getSquare(h_col,h_row)->getScore();

		}
		if(h_word!="")
		{
				std::pair<std::string, unsigned int> both2;
				both2=std::make_pair(h_word,score);
				contain_words.push_back(both2);
		}
	}
	if(!isHoriz)
	{
		size_t c_col=m.getX();
		size_t c_row=m.getY();
		std::string move_word=m.word();
		size_t length=move_word.length();
		size_t score=0;
		size_t index=0;
		size_t lmult=1;
		size_t wmult=1;
		//while index of tile string is less than length of word
		while(index<length )
		{
			std::string concatenate="";
			//if the left of a word is occupied, it will keep going left till the beginning of the word
			while((c_col-1)>0 && getSquare(c_col-1,c_row)->isOccupied())
			{
				c_col--;
			}
			//now we will go all the way to right the word 
			while(c_col<getColumns() && getSquare(c_col+1,c_row)->isOccupied())
			{
				//adding to the string
				concatenate+=getSquare(c_col,c_row)->getLetter();
				score+=getSquare(c_col,c_row)->getScore();
				c_col++;
				//if the next spot is empty but where the placemove string is going to be placed
				//then add from the player's hand
				if(!(getSquare(c_col+1,c_row)->isOccupied()))
				{
					//add to string
					concatenate+=move_word[index];
					//adjust lmult
					lmult=getSquare(c_col, c_row+1)->getLMult();
					//add to score
					score+= lmult*getSquare(c_col,c_row+1)->getScore();
					//adjust wmult
					wmult=wmult*getSquare(c_col,c_row+1)->getWMult();
					c_col++;
					continue;
				}
			}
			if(concatenate!="")
			{
				//now we add to vector of pairs
				score+=wmult;
				std::pair<std::string, unsigned int> both;
				both=std::make_pair(concatenate,score);
				contain_words.push_back(both);
			}
			index++;
		}
		size_t h_col=m.getX();
		size_t h_row=m.getY();
		size_t tileIndex=0;
		std::string h_word="";
		//go all the way to the top of the vertical word
		while(h_row-1>0 && getSquare(h_col,c_row-1)->isOccupied)
		{
			h_row--;
		}
		while(tileIndex<length)
		{
			if(getSquare(h_col,h_row)->isOccupied())
			{
				h_word+=getSquare(h_col,h_row)->getLetter();
				score+=getSquare(c_col,c_row)->getScore();
				h_row++;
			}
			//if not occupied, we will use corresponding index of tileString
			else
			{
				h_word+=move_word[tileIndex];
				score+=lmult*(hand[tileIndex]->getPoints());
				tileIndex++;
				h_row++;
			}
		}
		//if we run out of tiles, there could still be letters that appear after our
		//last used tile so we check for that 
		while(h_row<getRows() && getSquare(h_col,h_row)->isOccupied())
		{
			h_word+=getSquare(h_col,h_row)->getLetter();
			score+=getSquare(h_col,h_row)->getScore();

		}
		if(h_word!="")
		{
			std::pair<std::string, unsigned int> both2;
			both2=std::make_pair(h_word,score);
			contain_words.push_back(both2);
		}
	}
	return contain_words;
}

