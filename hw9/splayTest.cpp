#include<iostream>
#include "splayTree.h"
#include "print_bst.h"
using namespace std;
int main()
{
	splayTree<int,int> tree;
	tree.insert(make_pair(1, 1));
	tree.insert(make_pair(2, 1));
	tree.insert(make_pair(4, 1));
	tree.insert(make_pair(5, 1));
	tree.insert(make_pair(6, 1));
	tree.insert(make_pair(8, 1));
	tree.insert(make_pair(7, 1));
	tree.insert(make_pair(3, 1));
	//tree.findMax();
	//tree.findMax();
	//tree.findMax();
	//tree.findMin();
	tree.find(6);
	//tree.remove(2);
	//tree.remove(3);
	//tree.remove(5);
	//tree.deleteMinLeaf();
	//tree.deleteMaxLeaf();
	tree.print();
	return 0;
}

//Work on remove when you remove 7, splaying 6 works in that it is root but not the children
//when you find, nothing is splayed
//findMin isnt working correctly ()