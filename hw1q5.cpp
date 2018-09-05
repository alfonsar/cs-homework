#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>

int main (int argc, char* argv[])
{
  //checks if there is a second argument
  if(argc < 2)
  {
    std::cout << "Please provide a file in argument." << std::endl;
    return 1;
  }
  //grabs file from command line
  std::ifstream ifile;
  ifile.open(argv[1]);
  if(ifile.fail())
  {
  	std::cout<<"Can't open file"<<std::endl;
  	return 0;
  }

  int num;
  ifile>>num;
  if(ifile.fail())
  {
  	std::cout<<"Could not read file"<<std::endl;
  	return 0;
  }

  //dynamically allocate memory
  std::string* sentence= new std::string[num];
  for(int i=0;i<num;i++)
  {
  	//create a string to hold word 
  	std::string temp;
  	ifile>>temp;
  	//place word in string array location i
  	sentence[i]=temp;
  }
  //print out elements in the array
  for(int j=0;j<num;j++)
  {
  	//will print starting from back of array to front (reverse order)
  	std::cout<<sentence[num-1-j]<<std::endl;
  }

  //since we are done using sentence, we now free up memory
  delete [] sentence;
  return 0;
}
  