#include <string>
#include <set>
#include <vector>
#include<sstream>
#include "Player.h"
#include "Tile.h"

Player::Player (std::string const & name, size_t maxTiles,Bag& bag)
{
	first=name;
	score=0;
	max=maxTiles;
	//call the draw tiles which will draw tiles from bag
	std::vector<Tile*> newSet=bag.drawTiles(max);
	//we start the player off with a fresh new set of tiles at beginning of game
	for(std::vector<Tile*>::iterator it =newSet.begin(); it!=newSet.end();++it)
	{
		hand.insert(*it);
	}
	
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
bool Player::hasTiles(std::string const & move, bool resolveBlanks) const
{
	std::stringstream ss(move);
	std::string movetype;
	ss>>movetype;
	//Exchange move
	if(!resolveBlanks)
	{
		std::string bunchofletters;
		ss>>bunchofletters;
		std::set<Tile*>copy=hand;
		std::set<Tile*>::iterator it;
		for(int i=0;i<bunchofletters.size();i++)
		{
			if(bunchofletters[i]!='?'){std::toupper(bunchofletters[i]);}
			for(it=copy.begin();it!=copy.end();++it)
			{
				if((*it)->getLetter()==bunchofletters[i])
				{
					copy.erase(it);
					break;
				}
			}
			if(it==copy.end()){return false;}
		}
	}
	//Place move
	else
	{
		std::string dir;
		std:: string r;
		std:: string c;
		std:: string actualword;
		ss>>dir>>r>>c>>actualword;
		std::set<Tile*>copy=hand;
		std::set<Tile*>::iterator it;
		for(int i=0;i<actualword.size();i++)
		{
			if(actualword[i]!='?'){std::toupper(actualword[i]);}
			for(it=copy.begin();it!=copy.end();++it)
			{
				if((*it)->getLetter()==actualword[i])
				{
					if(actualword[i]=='?'){i++;}
					copy.erase(it);
					break;
				}
			}
			if(it==copy.end()){return false;}
		}
		return true;
	}
}
// Adds all the tiles in the vector to the player's hand.
void Player::addTiles (std::vector<Tile*> const & tilesToAdd)
{
	size_t num=tilesToAdd.size();
	for(size_t i=0; i<num;i++)
	{
		hand.insert(tilesToAdd[i]);
	}
	/*
	std::vector<Tile*>::iterator it;
	for(it=tilesToAdd.begin();it!=tilesToAdd.end();++it)
	{
		hand.insert(*it);
	}
	*/
}
std::set<Tile*> Player::getHandTiles() const
{
	return hand;
}
/* Reads a move string, finds the corresponding tiles in the player's hand, and
	   removes and returns those tiles in the order they appear in the move string.

	   The move string is case-insensitive.

	   The boolean resolveBlanks states whether this is a PLACE or EXCHANGE move.
	   If resolveBlanks is true, then when the string contains a '?',
	   the next letter is interpreted as the letter to use the blank as,
	   and the "use" field of the tile is set accordingly.

	   The move string is assumed to have correct syntax.
	*/
std::vector<Tile*> Player::takeTiles (std::string const & move, bool resolveBlanks)
{
	std::stringstream ss(move);
	std::string movetype;
	ss>>movetype;
	//Exchange move
	if(!resolveBlanks)
	{
		std::string bunchofletters;
		ss>>bunchofletters;
		std::vector<Tile*> return_tiles;
		std::set<Tile*>::iterator it;
		for(size_t i=0; i<move.size();i++)
		{
			for(it=hand.begin();it!=hand.end();++it)
			{
				if((*it)->getLetter()==move[i])
				{
					hand.erase(it);
					return_tiles.push_back(*it);
					break;
				}
			}
		}
		return return_tiles;
		
	}
	//Place move
	else
	{
		std::string dir;
		std:: string r;
		std:: string c;
		std:: string actualword;
		ss>>dir>>r>>c>>actualword;
		std::vector<Tile*> return_tiles;
		std::set<Tile*>::iterator it;
		for(size_t i=0; i<move.size();i++)
		{
			for(it=hand.begin();it!=hand.end();++it)
			{
				if((*it)->getLetter()==move[i])
				{
					hand.erase(it);
					return_tiles.push_back(*it);
					break;
				}
			}
		}
		return return_tiles;
	
	}

}