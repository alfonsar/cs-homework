#include<iostream>
#include "splayTree.h"
#include "print_bst.h"
using namespace std;
int main()
{
	std::cout<<"hello"<<std::endl;
	splayTree<int,int> tree;
	//tree.insert(make_pair(1, 1));
	tree.insert(make_pair(0, 1));
	tree.insert(make_pair(5, 1));
	tree.print();
	return 0;
}