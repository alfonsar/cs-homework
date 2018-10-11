#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <stdexcept>
#include "Dictionary.h"
using namespace std;

Dictionary::Dictionary (std::string dictionary_file_name){
	ifstream infile;
	std::string line;
	infile.open(dictionary_file_name);
	while(getline(infile,line)){
		if(allwords.end()==allwords.find(line)){allwords.insert(line);}
	}
}


	/* Checks whether the given word is in the dictionary, and returns true if so.
	   Case should not matter. Must run in O(logn) for the number of words in the dictionary. */
bool Dictionary::isLegalWord (std::string const & word) const{
	//makes the words capital
	transform(word.begin(),word.end(),word.begin(),::toupper);
	//if not found in dictionary, then not legal
	if(allwords.end()==allwords.find(word)){return 0;}
	return 1;
}
