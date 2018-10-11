#include <vector>
#include <string>
#include "Tile.h"
#include "Player.h"
#include "Bag.h"
#include "Dictionary.h"
#include "Move.h"

ExchangeMove::ExchangeMove(std::string tileString, Player* p)
{
    for(size_t j=0; j<tileString.length();j++)
    {
        xtiles+=std::toupper(tileString[j]);
    }
    player=p;
}

/* Executes this move, whichever type it is.
    This may throw exceptions; students: it's up to you to
    decide (and document) what exactly it throws*/
void ExchangeMove::execute(Board & board, Bag & bag, Dictionary & dictionary)
{
    std::vector<Tile*>tiles_bag;
    tiles_bag=player->takeTiles(xtiles,false);
    bag.addTiles(tiles_bag);
    player->erasefromHand(xtiles);
    //grab amount of tiles they discarded from the bag
    std::vector<Tile*> brandNew=bag.drawTiles(xtiles.length()); 
    std::vector<Tile*> ::iterator it;
    for(it=brandNew.begin();it!=brandNew.end();++it)
    {
        player->hand.insert(*it);
    }
}