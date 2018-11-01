#include<iostream>
#include<ostream>
#include<fstream>
#include<vector>
#include <set>

struct Country
{
	char name;
	int color;
	std::set<char> neighbors;

};

int main(int argc, char* argv[])
{
	//if no parameter is given, exit
    if(argc<2) {return -1;}
    //create an infile to open textfile
    std::ifstream infile;
    infile.open(argv[1]);
    int columns, rows, numCountries;
    //read in the number of letters, rows, columns
    infile>>numCountries>>rows>>columns;
    //create a 2d vector to visualize graph
    std::vector<std::vector<char> > graph;
    //we now resize the 2d vector to the appropriate lengths
    graph.resize(rows, std::vector<char>(columns));
    //creating the graph
    for(int j=0; j<rows; j++)
    {
        for(int k=0; k<columns;k++)
        {   
            char let;
            infile>>let;
            graph[j][k]=let;
        }
    }

    for(int i=0;i<rows;i++)
   
    /*
    std::vector<std::set<char> > mapping;
    for(int j=0; j<numCountries;j++)
    {
    	std::set<char> input;
    	mapping.push_back(input);
    }
   */
	return 0;
	
}