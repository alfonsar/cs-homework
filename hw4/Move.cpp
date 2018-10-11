#include <string>
#include <set>
#include <iostream>
#include <map>
#include <vector>
#include "Tile.h"
#include "Square.h"
#include "Move.h"
#include "Dictionary.h"

Move::Move(){
	
}
/* Parses the given move m, and constructs the corresponding move subclass.
	   m is assumed to be in the format described on the assignment sheet for a move command.
	   The player passed in is used to verify that the proposed tiles are
	   in fact in the player's hand.
	   It can handle all three types of move (PASS, EXCHANGE, PLACE).
	   Coordinates start with 1.
	*/
 Move * Move::parseMove(std::string moveString, Player &p)
{
  if(moveString=="EXCHANGE")
  {
     //after exchange we read in the move string
      std::string tilesInHand;
      std::cin>>tilesInHand;
      //call the exchange function with movestring
      ExchangeMove* exchanger= new ExchangeMove(tilesInHand,&p);
      return exchanger;
  }
  else if (moveString=="PLACE")
  {
      //read in values
      char direction;
      size_t input_row=0;
      size_t input_col=0;
      std::string tilesInHand="";
      bool horiz;
      std::cin>>direction;
      //from the char we determine orientation of word
      if(direction=='-') 
      {
          horiz=true;
      }
      else{ horiz=false;}
      std::cin>>input_row>>input_col>>tilesInHand;
      //call function
      PlaceMove* placer= new PlaceMove(input_row,input_col,horiz,tilesInHand,&p);
      return placer;
  }
  else if (moveString=="PASS")
  {
      PassMove* passer=new PassMove(&p);
      return passer;
  }

}
