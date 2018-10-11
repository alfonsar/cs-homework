#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <stdexcept>
#include "Board.h"
#include "Player.h"
#include "ConsolePrinter.h"
#include "Bag.h"
#include "Dictionary.h"
void readFile(std::string file_name,int& hand, std::string&tilers, std::string& dict, std::string& boarders,int&seed)
{
	std::ifstream infile(file_name);
	std::string line;
	while(std::getline(infile,line)){
		std:: stringstream ss(line);
		std::string what;
		ss>>what;
		if(what=="HANDSIZE:"){ss>>hand;}
		if(what=="TILES:"){ss>>tilers;}
		if(what=="DICTIONARY:"){ss>>dict;}
		if(what=="BOARD:"){ss>>boarders;}
		if(what=="SEED:"){ss>>hand;}
	}
}

int main(int argc, char*argv[])
{
	if(argc<2){return -1;}
	int handsize,seed;
	std::string tiles, board,diction;
	readFile(argv[1],handsize,tiles,diction,board,seed);
	Dictionary dictionary(diction);
	Board boardgame(board);
	Bag bag(tiles,seed);
	std::cout<<"How many players?"<<std::endl;
	size_t numofPlayers;
	std::cin>>numofPlayers;
	std::vector<Player>players;
	for(size_t i=1; i<=numofPlayers;i++)
	{
		std::string first_name;
		std::cout<<"Enter player "<<i<<" name:";
		std::cin>>first_name;
		//filling vectors with the particular names and their other parameters 
		//such as handsize and the bag
		players.push_back(Player(first_name,handsize,bag));
	}
	ConsolePrinter console;

	std::vector<Player>::iterator it;
	for(size_t i=0;i<10;i++)
	{
		for(it=players.begin();it!=players.end();++it)
		{
			console.printBoard(board);
			console.printHand(*it);
			std::cout<<(*it).firstName()<<" enter a move: ";
			std::string turn;
			std::cin>>turn;
			std::string typeOfTurn="";
			for(size_t j=0; j<turn.length();j++)
			{
				typeOfTurn+=std::toupper(turn[j]);
			}
			Move * playerTurn = Move::parseMove(typeOfTurn,(*it));
			playerTurn->execute(boardgame,bag,dictionary);
			console.printBoard(board);
			console.printHand(*it);
			std::cout<<"Enter to continue"<<std::endl;
			std::cin.clear();
			std::cin.ignore();	
		}
	}

	return 0;
}