#include "Dictionary.h"
#include<string>
#include<set>


Dictionary::Dictionary (std::string dictionary_file_name){
	ifstream infile(dictionary_file_name);
	std::string line;
	infile.open();
	while(getline(infile,line)){
		if(allwords.end()==allwords.find(line)){allwords.insert(line);}
	}
}


	/* Checks whether the given word is in the dictionary, and returns true if so.
	   Case should not matter. Must run in O(logn) for the number of words in the dictionary. */
bool Dictionary::isLegalWord (std::string const & word) const{
	transform(word.begin(),word.end(),word.begin(),::tolower());
	if(allwords.end()!=allwords.find(word)){return 1;}
	return 0;
}
