#ifndef PLAYER_H_
#define PLAYER_H_

#include <string>
#include <set>
#include <vector>

#include "Tile.h"

Player::Player (std::string const & name, size_t maxTiles)
{
	first=name;
	score=0;
}


	/* Reads a move string and confirms that the player has the tiles necessary to
	   execute this move.

	   The move string is case-insensitive.

	   The boolean resolveBlanks states whether this is a PLACE or EXCHANGE move.
	   If resolveBlanks is true, then when the string contains a '?',
	   the next letter is interpreted as the letter to use the blank as.

	   By definition, if this function returns true, then takeTiles() would
	   succeed.
	 */

bool hasTiles(std::string const & move, bool resolveBlanks) const{
	
}