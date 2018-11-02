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
bool comparing(Country lhs, Country rhs)
{
    return (lhs.name<rhs.name);
}
void findNeighbors(std::vector<Country>&country, std::vector<std::vector<char> > graph, int rows, int columns)
{
 
    int c_row;
    int c_col;
    std::vector<Country>::iterator it;
    for(it=country.begin();it!=country.end();++it)
    {
        std::queue<std::pair<int, int> >look;
        std::set< std::pair<int, int> >isVisited;
        look.push(it->loc);
        isVisited.insert(it->loc);
        char checker=it->name;
        while(!look.empty())
        {
            c_row=look.front().first;
            c_col=look.front().second;
            //char checker=graph[c_row][c_col];
            look.pop();
            if(c_row-1>=0)
            {
                std::pair<int,int>rowAbove(c_row-1,c_col);
                if(graph[c_row-1][c_col]==checker && isVisited.find(rowAbove)==isVisited.end())
                {
                    look.push(rowAbove);
                    isVisited.insert(rowAbove);
                    //currentCountry++;
        
                }
                else if(graph[c_row-1][c_col]!=checker && (isVisited.find(rowAbove)==isVisited.end()))
                {   
                    std::vector<Country>::iterator it2;
                    for(it2=country.begin();it2!=country.end();++it2)
                    {
                        if(graph[c_row-1][c_col]==it2->name)
                        {
                            it->neighbors.insert(&(*it2));
                            break;
                        }
                    }
                   
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
            if(newCountry)
            {
                Country acountry;
                acountry.name=graph[j][k];
                std::pair<int,int> add (j,k);
                acountry.loc.first = add.first;
                acountry.loc.second = add.second;
                acountry.color=1;
                vect.push_back(acountry);
            }
            
        }
    }
    findNeighbors(vect,graph,rows,columns);
    std::set<Country*>::iterator it;
    for (size_t i = 0; i < vect.size(); i++) {
        std::cout << vect[i].name << "'s neighbors are: ";
        for (it = vect[i].neighbors.begin(); it != vect[i].neighbors.end(); ++it) {
            std::cout << (*it)->name << " ";
        }
        std::cout << std::endl;
    }
    for(int i=0; i<vect.size();i++)
    {
        for(it=vect[i].neighbors.begin();it!=vect[i].neighbors.end();++it)
        {   
            if(vect[i].color==(*it)->color)
            {
                ((*it)->color)++;
            }
        }
    }
   std::sort(vect.begin(),vect.end(),comparing);
//    int len=vect.size();
//     for(int i=0; i<len;i++)
//     {
//         std::cout<<vect[i].name<<" "<<vect[i].color<<std::endl;
//     }

	return 0;
}