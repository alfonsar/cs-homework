#include "duck_duck_goose.h"
#include <iostream>
#include <ostream>
#include <fstream>
#include "circular_list_int.h"

void simulateDDGRound(GameData * gameData, std::ostream & output)
{
	//because 
	int tot_players=gameData->playerList.size();
	while(gameData->itPlayerID!=0)
	{
		int m= rand() % (4*tot_players);
		//for loop to go down the list m times
		for(int i=0;i<m;i++)
		{
			output<<gameData->playerList.get(i)<<" is a Duck.\n";
		}
		//after m times, we pick the goose and print out statement
		output<<gameData->playerList.get(m)<< " is a Goose!\n";
		//it picks a random number
		int it_rand=(rand() %50);
		//goose picks random number
		int goose_rand=(rand()%50);
		//if their numbers are the same, then repick values
		while(it_rand==goose_rand)
		{
			it_rand=rand()%50;
			goose_rand=rand()%50;
		}
		//if the it player has a higher number
		if (it_rand>goose_rand)
		{
			//it takes goose's spot (m)
			gameData->playerList.set(m,gameData->itPlayerID);
			//output statement
			output<<gameData->itPlayerID<<" took "<<gameData->playerList.get(m)<<"'s spot!\n";
			//goose becomes the new IT
			gameData->itPlayerID=gameData->playerList.get(m);
		}
		//if goose has a higher number
		else if(goose_rand>it_rand)
		{
			output<<gameData->itPlayerID<<" is out!\n";
			//if goose is the only one, the goose wins
			if((gameData->playerList.size())==1)
			{
				output<<"Winner is "<<gameData->playerList.get(m)<<"!\n";
				//if there is a winner, then set player id to 0
				gameData->itPlayerID=0;			}
			else
			{
				//pick new it
				int new_it=rand() %(tot_players);
				//set itPlayerID to new id
				gameData->itPlayerID=gameData->playerList.get(new_it);
				//dcheck to make sure that new it is not goose
				while(gameData->itPlayerID==gameData->playerList.get(m))
				{
					//if it is generate a new rand position
					new_it=rand() % (tot_players);
					gameData->itPlayerID=gameData->playerList.get(new_it);
				}
				//remove from list
				gameData->playerList.remove(new_it);
				output<<gameData->itPlayerID<<" was chosen as the new it.\n";
				
				
			}
		}
	}
}
int main (int argc, char* argv[])
{
	if(argc<3)
	{
		return -1;
	}

	std::ifstream infile;
	infile.open(argv[1]);
	//create struct
	GameData* gameData= new GameData();
	//grabs seed
	unsigned int seed;
	//numsber of players
	size_t num_plays;
	infile>>seed>>num_plays>>gameData->itPlayerID;
	//generate seeds
	srand(seed);
	//store id of player
	size_t player_id;
	while(!infile.fail())
	{
		infile>>player_id;
		//add to circular list the player's id
		gameData->playerList.push_back(player_id);

	}
	std::ofstream out_file;
	out_file.open(argv[2]);

	simulateDDGRound(gameData, out_file);
	
	delete gameData;
	return 0;
}