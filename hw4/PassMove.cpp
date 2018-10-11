#include <vector>
#include <string>
#include "Tile.h"
#include "Player.h"
#include "Move.h"
#include "Bag.h"
#include "Dictionary.h"
#include "ConsolePrinter.h"

void PassMove::execute(Board & board, Bag & bag, Dictionary & dictionary)
{
    std::cout<<"These are your current tiles: "<<player->printHand()<<std::endl;
}