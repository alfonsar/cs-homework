#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <stdexcept>

void readFile(string file_name;int& hand, std::string&tilers, std::string& dict, std::string& boarders,int&seed){
	ifstream infile(file_name);
	std::string line;
	while(getline(infile,line)){
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
	std::string tiles, board,dictionary;
	readFile(argv[1],handsize,tiles,dictionary,board,seed);
	std::cout<<"How many players?"<<std::endl;
	int numofPlayers;
	std::cin>>numofPlayers;

	return 0;
}