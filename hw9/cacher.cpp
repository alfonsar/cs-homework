#include "cacheLRU.h"
#include <iostream>
#include<ostream>
#include<fstream>
#include<sstream>
#include <utility>
#include "print_bst.h"
using namespace std;
int main(int argc, char* argv[])
{
	cacheLRU<int,int> cacher(1000);
	std::pair<int,int> yes;
	//yes=make_pair(1,1);
	//no=make_pair(2,2);
	//cacher.put(yes);
	//cacher.put(no);
	
	//if no parameter is given, exit
    if(argc<2) {return -1;}
    //create an infile to open textfile
    ifstream infile;
    infile.open(argv[1]);
    //string word;
    int counter=1;
    int num;
    while(infile>>num)
    {
    	//cout<<num<<endl;
    	yes=make_pair(num,counter);
    	cacher.put(yes);
    	counter++;
    }
    cout<<"Total words: "<<counter<<std::endl;
 	cacher.print();
	return 0;
}
