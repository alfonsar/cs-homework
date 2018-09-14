#include "duck_duck_goose.h"
#include <iostream>
#include <ostream>
#include <fstream>
#include "circular_list_int.h"

void simulateDDGRound(GameData * gameData, std::ostream & output)
{
	size_t tot_players=gameData->playerList.size();
	while(gameData->itPlayerID!=0)
	{
		size_t m= rand() % (4*tot_players);
		//for loop to go down the list m times
		for(size_t i=0;i<m;i++)
		{
			output<<gameData->playerList.get(i)<<" is a Duck.\n";
		}
		//after m times, we pick the goose and print out statement
		output<<gameData->playerList.get(m)<< " is a Goose!\n";
		//it picks a random number
		size_t it_rand=(rand() %50);
		//goose picks random number
		size_t goose_rand=(rand()%50);
		//if their numbers are the same, then repick values
		while(it_rand==goose_rand)
		{
			it_rand=rand()%50;
			goose_rand=rand()%50;
		}
		//if the it player has a higher number
		if (it_rand>goose_rand)
		{
			gameData->playerList.set(m,gameData->itPlayerID);
			output<<gameData->itPlayerID<<" took "<<gameData->playerList.get(m)<<"'s spot!\n";
			gameData->itPlayerID=gameData->playerList.get(m);
		}
		else if(goose_rand>it_rand)
		{
			output<<gameData->itPlayerID<<" is out!\n";
			if((gameData->playerList.size())==1)
			{
				output<<"Winner is "<<gameData->playerList.get(m)<<"!\n";
				gameData->itPlayerID=0;			}
			else
			{
				size_t new_it=rand() %(tot_players);
				gameData->itPlayerID=gameData->playerList.get(new_it);
				while(gameData->itPlayerID==gameData->playerList.get(m))
				{
					new_it=rand() % (tot_players);
					gameData->itPlayerID=gameData->playerList.get(new_it);
				}
				
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
	while(gameData->itPlayerID!=0)
	{
		simulateDDGRound(gameData, out_file);
	}
	delete gameData;
	return 0;
}