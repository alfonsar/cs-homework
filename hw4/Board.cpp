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
	return boardgame[x][y];
}
bool Board::firstMove(){
	if(boardgame[sx][sy].isOccupied()==0){return true;}
	return false;
}
size_t Board::getRows() const{
	return rows;
}

/* Returns the number of columns of the board.*/
size_t Board::getColumns() const{
	return columns;
}
size_t Board::getsx(){
	return sx;
}
size_t Board::getsy(){
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
std::vector<std::pair<std::string, unsigned int>> PlaceMove::getPlaceMoveResults(const PlaceMove &m) const
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
		while(index<length)
		{
			//&& getSquare(c_col-1,c_row)->isOccupied()
			std::string concatenate="";
			//if the top of a letter is occupied, it will keep going up till the top of the word
			while((c_row-1)>0 && getSquare(c_col+1,c_row)->isOccupied())
			{
				c_col--;
			}
			//now we will go all the way down the word 
			while(c_col<getColumns() && getSquare(c_col+1,c_row)->isOccupied())
			{
				//adding to the string
				concatenate+=getSquare(c_col,c_row)->getLetter();
				score+=getSquare(c_col,c_row)->getScore();
				c_col++;
				//if the next spot is empty but where the placemove string is going to be placed
				//then add from the player's hand
				if(c_row+1==m.getY())
				{
					concatenate+=move_word[index];
					lmult=getSquare(c_col+1, c_row)->getLMult();
					score+= lmult*getSquare(c_col+1,c_row)->getScore();
					wmult=wmult*getSquare(c_col+1,c_row)->getWMult();
					c_col++;
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
		while(index<length )
		{
			//&& getSquare(c_col,c_row-1)->isOccupied()
			std::string concatenate="";
			//if the top of a letter is occupied, it will keep going up till the top of the word
			while((c_row-1)>0 && getSquare(c_col+1,c_row)->isOccupied())
			{
				c_row--;
			}
			//now we will go all the way down the word 
			while(c_col<getColumns() && getSquare(c_col,c_row+1)->isOccupied())
			{
				//adding to the string
				concatenate+=getSquare(c_col,c_row)->getLetter();
				score+=getSquare(c_col,c_row)->getScore();
				c_row++;
				//if the next spot is empty but where the placemove string is going to be placed
				//then add from the player's hand
				if(!(getSquare(c_col+1,c_row)->isOccupied()))
				{
					concatenate+=move_word[index];
					lmult=getSquare(c_col, c_row+1)->getLMult();
					score+= lmult*getSquare(c_col,c_row+1)->getScore();
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
	}
	return contain_words;
}

