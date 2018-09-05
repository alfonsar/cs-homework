
#include <iostream>
#include <sstream>
#include <cstring> 

//using namespace std;

bool helper (std::stringstream &input, int len)
{
	char prev;

	//if we are at the midpoint of the string, return true.
	if (len == 0) return true;

	/**
	 * If the length of the string is odd, and the next
	 * character is the midpoint of the string, consume it
	 * and return true.
	 */
	input >> prev;
	if (len == 1) return true;

	bool val = helper(input, len-2);

	//make your changes only below this line.
	char last; //creates a char
 	input>>last;  //puts in char from ss stream into last variable
	if (last==prev) return true; //will compare the first and last variables
	return false;
	 
}

//do not change the main function.
int main (int argc, char* argv[])
{
  if(argc < 2){
    std::cout << "Please provide a string of characters." << std::endl;
    return 1;
  }
  std:: stringstream ss;
   ss << argv[1];
  if(helper(ss, strlen(argv[1])))
	  std::cout << "Palindrome" << std::endl;
  else std::cout << "Not a Palindrome" << std::endl;
  return 0;
}
