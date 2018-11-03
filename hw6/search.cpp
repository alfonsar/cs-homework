#include<iostream>
#include<ostream>
#include<fstream>
#include <queue>
#include <set>
#include<sstream>
#include <vector>

int main(int argc, char* argv[])
{
    //if no parameter is given, exit
    if(argc<2) {return -1;}
    //create an infile to open textfile
    std::ifstream infile;
    infile.open(argv[1]);
    int columns, rows, numLetters;
    //read in the number of letters, rows, columns
    infile>>numLetters>>rows>>columns;
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
    //use the queue to store the rows/columns of the graph
    std::queue<std::pair<int,int> > look;
    std::set<std::pair<int,int> > isVisited;
    std::pair<int,int>first(0,0);
    //we push since this is the starting pos of first node
    look.push(first);
    //mark as visited
    isVisited.insert(first);

    int biggestCountry=-1;
    int currentCountry=1;
    int n_row=0;
    int n_col=0;
    bool flag=false;
    int c_row;
    int c_col;
    while(!look.empty())
    {
        c_row=look.front().first;
        c_col=look.front().second;
        char checker=graph[c_row][c_col];
        look.pop();
        //checking the top of the letter and make sure it is in bounds
        if(c_row-1>=0)
        {
            std::pair<int,int> rowAbove(c_row-1,c_col);
            //check to see if the above letter is apart of the country and it has not been visited
            if(graph[c_row-1][c_col]== checker && isVisited.find(rowAbove)==isVisited.end())
            {
                //push on the queue if correct letter but have not yet visited
                look.push(rowAbove);
                //mark as visited by inserting into set
                isVisited.insert(rowAbove);
                //increase the country's size
                currentCountry++;
            }
            else if(graph[c_row-1][c_col]!=checker && (isVisited.find(rowAbove)==isVisited.end()))
            {   
                flag=true;
                //if a different letter, we are going flag it and store the next column and row 
                n_col=c_col;
                n_row=c_row-1;
            }
        }
        if(c_row+1<rows)
        {
            //create a pair containing the locations (row,column) of node
            std::pair<int,int> rowBelow(c_row+1,c_col);
            if(graph[c_row+1][c_col]==checker && isVisited.find(rowBelow)==isVisited.end())
            {
                //push on queue if the correct letter but have not yet visited
                look.push(rowBelow);
                //mark as visited by inserting into set
                isVisited.insert(rowBelow);
                //increase the country's size
                currentCountry++;
            }
            else if(graph[c_row+1][c_col]!=checker && (isVisited.find(rowBelow)==isVisited.end()))
            {
                flag=true;
                //if its a different letter, we are going to flag it and store the next column and row
                n_col=c_col;
                n_row=c_row+1;
            }
        }
        if(c_col-1>=0)
        {
            //create a pair containing the locations (rows, column) of node
            std::pair<int,int> colLeft(c_row,c_col-1);
            if(graph[c_row][c_col-1]==checker && isVisited.find(colLeft)==isVisited.end())
            {
                //push on queue if the correct letter but have not yet visited
                look.push(colLeft);
                //mark as visited by inserting into set
                isVisited.insert(colLeft);
                //increase the country's size
                currentCountry++;
            }
            else if(graph[c_row][c_col-1]!=checker && (isVisited.find(colLeft)==isVisited.end()))
            {
                flag=true;
                //if its a different letter, we are going to flag it and store the next column and row
                n_col=c_col-1;
                n_row=c_row;
            }
        }
        if(c_col+1<columns)
        {
            //create a pair containing the locations (row, column) of node
            std::pair<int,int> colRight(c_row,c_col+1);
            if(graph[c_row][c_col+1]==checker && isVisited.find(colRight)==isVisited.end())
            {
                //push on queue if the correct letter but have not yet visited
                look.push(colRight);
                //mark as visited by inserting into set
                isVisited.insert(colRight);
                //increase the countries size
                currentCountry++;
            }
            else if(graph[c_row][c_col+1]!=checker && (isVisited.find(colRight)==isVisited.end()))
            {
                flag=true;
                //if its a different letter, we are going to flag it and store the next column and row 
                n_col=c_col+1;
                n_row=c_row;
            }
        }
        if(look.empty())
        {
            if (!flag) {
            	//assign current country biggest if 
                //its greater than biggestCountry
                if (currentCountry > biggestCountry) {
            		biggestCountry = currentCountry;
            	}

            }
            else {
	            //else make of pair of the next 
                //letter found and push
                std::pair<int,int> add(n_row,n_col);
	            look.push(add);
                isVisited.insert(add);
	            if(currentCountry>biggestCountry) 
	            {
	                biggestCountry=currentCountry;
	            }
	            currentCountry = 1;
	            flag=false;
	            c_col=n_col;
	            c_row=n_row;
            }

        }   
    }
    std::cout<<biggestCountry<<std::endl;

    return 0;
}