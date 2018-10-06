#ifndef BOARD_H_
#define BOARD_H_

#include <string>
#include <set>
#include <map>
#include <vector>
#include "Tile.h"
#include "Square.h"
#include "Move.h"
#include "Dictionary.h"

Board::Board (std::string board_file_namey){
	ifstream infile(board_file_namey);
	infile.open();
	infile>>rows>>columns>>sx>>sy;
	
	for(size_t i=0; i<rows;i++){
		for(size_t j=0; j<columns;j++){
			char current;
			ifile>>current
			int Lmult=1;
			int Wmult=1;
			if(current=='2'){Lmult=2;}
			if(current=='3'){Lmult=3;}
			if(current=='d'){Wmult=2;}
			if(current=='t'){Wmult=3;}
			if(i==sx&&j==sy){Square yes(Lmult,Wmult,1);}
			else{Square yes(Lmult,Wmult,0)}
			boardgame[i][j]=yes;
		}
	}
}

bool Board::firstMove(){
	if(boardgame[sx][sy].isOccupied()==1){return true;}
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
size_t Board::getxy(){
	return sy;
}

