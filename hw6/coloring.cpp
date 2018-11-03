#include<iostream>
#include<ostream>
#include<fstream>
#include<vector>
#include <set>
#include <queue>

struct Country
{
	char name;
	int color;
    std::pair<int,int>loc;
	std::set<Country*> neighbors;

};
//function to alphabetize the names of the nodes by letter
bool comparing(Country lhs, Country rhs)
{
    return (lhs.name<rhs.name);
}
//function mostly grabbed search.cpp that I wrote for hw6 problem 1
void findNeighbors(std::vector<Country>&country, std::vector<std::vector<char> > graph, int rows, int columns)
{
 
    int c_row;
    int c_col;
    //iterate through the vector of countries
    std::vector<Country>::iterator it;
    for(it=country.begin();it!=country.end();++it)
    {
        std::queue<std::pair<int, int> >look;
        std::set< std::pair<int, int> >isVisited;
       //will push the initial locations into queue and set
        look.push(it->loc);
        isVisited.insert(it->loc);
        char checker=it->name;
        while(!look.empty())
        {
            c_row=look.front().first;
            c_col=look.front().second;
            look.pop();
            //check above
            if(c_row-1>=0)
            {
                std::pair<int,int>rowAbove(c_row-1,c_col);
                if(graph[c_row-1][c_col]==checker && isVisited.find(rowAbove)==isVisited.end())
                {
                    look.push(rowAbove);
                    isVisited.insert(rowAbove);        
                }
                else if(graph[c_row-1][c_col]!=checker && (isVisited.find(rowAbove)==isVisited.end()))
                {   
                    std::vector<Country>::iterator it2;
                    for(it2=country.begin();it2!=country.end();++it2)
                    {
                        if(graph[c_row-1][c_col]==it2->name)
                        {
                           //inserting neighbors
                            it->neighbors.insert(&(*it2));
                            break;
                        }
                    }
                   
                }
            }
            //check below
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
                }
                else if(graph[c_row+1][c_col]!=checker && (isVisited.find(rowBelow)==isVisited.end()))
                {
                    std::vector<Country>::iterator it2;
                    for(it2=country.begin();it2!=country.end();++it2)
                    {
                        if(graph[c_row+1][c_col]==it2->name)
                        {
                            it->neighbors.insert(&(*it2));
                            break;
                        }
                    }
                
                }
            }
            //check left
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
                }
                else if(graph[c_row][c_col-1]!=checker && (isVisited.find(colLeft)==isVisited.end()))
                {
                    std::vector<Country>::iterator it2;
                    for(it2=country.begin();it2!=country.end();++it2)
                    {
                        if(graph[c_row][c_col-1]==it2->name)
                        {
                            it->neighbors.insert(&(*it2));
                            break;
                        }
                    }
                   
                }
            }
            //check right
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
                }
                else if(graph[c_row][c_col+1]!=checker && (isVisited.find(colRight)==isVisited.end()))
                {
                    std::vector<Country>::iterator it2;
                    for(it2=country.begin();it2!=country.end();++it2)
                    {
                        if(graph[c_row][c_col+1]==it2->name)
                        {
                            it->neighbors.insert(&(*it2));
                            break;
                        }
                    }
                  
                }
            }
           
        }
    }
}
//checking to see if the colors of the neighbors of the node are all different
bool good(Country* c_country, int c_color)
{
    //now will iterate through our set of neighbors
    std::set<Country*>::iterator it;
    for(it=c_country->neighbors.begin();it!=c_country->neighbors.end();++it)
    {
        //if there are neigbors that share the same color
        //as the parent, then not good
        if((*it)->color==c_color)
        {
            return false;
        }
    }
    return true;
}   
bool backing(Country* c_country, std::vector<Country>&entity)
{
    for(int i=1;i<=4;i++)
    {
        c_country->color=i;
        if(good(c_country,c_country->color))
        {
            Country* next=nullptr;
            int len =entity.size();
            for(int k=0; k<len;k++)
            {
                if(entity[k].color==-1)
                {
                    next=&entity[k];
                    break;
                }
            }
            if(next==nullptr) return true;
            if(backing(next, entity)) return true;
            else continue;
        }
        else continue;
    }
    c_country->color=-1;
    return false;
}

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
    std::vector<Country> vect;
    //creating the graph
      
    for(int j=0; j<rows; j++)
    {
        for(int k=0; k<columns;k++)
        {   
           //reading in the graph
            char let;
            infile>>let;
            graph[j][k]=let;
            std::vector<Country>::iterator it;
            bool newCountry=true;
            for(it=vect.begin();it!=vect.end();++it)
            {
                if(graph[j][k]==it->name)
                {
                    newCountry=false;
                    break;
                }
            }
            //if it encounters a new letter, make a
            //struct for it
            if(newCountry)
            {
                //create a new country
                Country acountry;
                //assign the name
                acountry.name=graph[j][k];
                //create a pair
                std::pair<int,int> add (j,k);
                //assign its indices using pairs
                acountry.loc.first = add.first;
                acountry.loc.second = add.second;
                //give it an initial value
                acountry.color=-1;
                vect.push_back(acountry);
            }
            
        }
    }
    //used to assign the neighbors
    findNeighbors(vect,graph,rows,columns);
    //backtracking implementation
    backing(&vect[0],vect);
    //used to alphabetize the vector of structs 
    //by letter
    std::sort(vect.begin(),vect.end(),comparing);
    int sizer=vect.size();
    //display the nodes and 
    //corresponding colors
    for(int k=0; k<sizer;k++)
    {
        std::cout<<vect[k].name<<" "<<vect[k].color<<std::endl;
    }


	return 0;
}