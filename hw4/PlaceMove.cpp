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
}


