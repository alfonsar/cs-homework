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
			delete gameboard[i][j];
		}
	}
	//delete gameboard[][];
}

/* Returns a pointer to the Square object representing the
   (y,x) position of the board. Indexing starts at 1 here.
   This is needed only to display the board. */
Square Board:: getSquare (size_t x, size_t y) const
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
std::vector<std::pair<std::string, unsigned int>> Board::getPlaceMoveResults(const PlaceMove &m) const
{

}


