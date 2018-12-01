//
// Dictionary class implementation from Jamie's solution
//

#include <string>
#include <fstream>

#include "Dictionary.h"
#include "Exceptions.h"
#include "Trie.h"
#include "Util.h"

Dictionary::Dictionary(std::string dictionary_file_name):
words()
{
	std::ifstream dictFileStream(dictionary_file_name);

	if(!dictFileStream)
	{
		throw FileException("DICTIONARY");
	}

	while(!dictFileStream.eof())
	{
		std::string word;
		dictFileStream >> word;

		if (dictFileStream.eof() && word.empty())
		{
			break;
		}

		makeLowercase(word);
		words.insert(word);
	}
}

Dictionary::~Dictionary()
{
	// default destructor is OK
}

bool Dictionary::isLegalWord(std::string const &word) const
{
	
	std::string lowercaseWord(word);
	makeLowercase(lowercaseWord);
	//return words.find(lowercaseWord) != words.end();
	TrieNode* node=prefix(lowercaseWord);
	if(node==NULL) return 0;
	if(!node->inSet) return 0;
	return 1;
}
