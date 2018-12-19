#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>
#include <vector>
#include<algorithm>
#include "bst.h"
#include "rotateBST.h"

template <typename Key, typename Value>
class splayTree: public rotateBST<Key, Value>{
    public:
        splayTree();
        void insert(const std::pair<const Key, Value>& keyValuePair)
        {
        	//do an ordinary binary tree insert
        	BinarySearchTree<Key,Value>::insert(keyValuePair);
        	//once we do that, we need to go to that node
        	//so that we can splay it
        	Node<Key,Value>* place=this->mRoot;
        	while(place->getKey()!=keyValuePair.first)
        	{
        		if(keyValuePair.first>place->getKey())
        		{
        			place=place->getRight();
        		}
        		else if (keyValuePair.first<place->getKey())
        		{
        			place=place->getLeft();
        		}
        	}
        	splay(place);
        }
        void remove(const Key& key);
        typename splayTree<Key, Value>::iterator find(const Key& key)
        {
        	Node<Key,Value>* place=this->mRoot;
        	//if we point to node and it is null
        	//then the tree is empty
        	if(place==nullptr) 
        	{
        		typename splayTree<Key, Value>::iterator finder(nullptr);
        		return finder;
        	}
        	//if the root is the key, we return iterator
        	//to root and since it is root, we dont need to splay it 
        	if(place->getKey()==key) 
        	{
        		typename splayTree<Key,Value>::iterator finder(place);
        		return finder;
        	}
        	//will be used to hold the node before my traversing 
        	//node
        	Node<Key,Value>* before=nullptr;
        	//while place is not null
        	while(!place)
        	{
        		//set it equal to place everytime
        		before=place;
        		//if key is less than current node, 
        		//we move down to left child
        		if(key<place->getKey())
        		{
        			place=place->getLeft();
        		}
        		//if key is greater than current node,
        		//we move down to right child
        		else if(key>place->getKey())
        		{
        			place=place->getRight();
        		}
        		//otherwise we have found the node
        		else
        		{
        			//now splay and return an iterator to that
        			splay(place);
        			typename splayTree<Key,Value>::iterator finder(place);
        			return finder;
        		}
        	}
        	//if we ever reach this point, it means the key was not
        	//in tree so return null ptr
        	splay(before);
        	typename splayTree<Key,Value>::iterator finder(nullptr);
        	return finder;

        }
        //function to find minimum leaf and then splay it
        typename splayTree<Key, Value>::iterator findMin()
        {
        	//make pointer to root
        	Node<Key,Value>* place=this->mRoot;
        	//if root is null, it is empty so return 
        	//null iterator
        	if(place==nullptr)
        	{
        		typename splayTree<Key,Value>::iterator finder(nullptr);
        		return finder;
        	}
        	//will be used to hold the node before my traversing node
        	Node<Key,Value>* before=nullptr;
        	//while place is not null
        	while(place!=nullptr)
        	{
        		before=place;
        		//keep moving down left child
        		place=place->getLeft();
        	}
        	splay(before);
        	typename splayTree<Key,Value>::iterator finder(before);
        	return finder;
        }
        //function to find max node and then splay it
        typename splayTree<Key, Value>::iterator findMax()
        {
        	Node<Key,Value>* place=this->mRoot;
        	if(place==nullptr)
        	{
        		typename splayTree<Key,Value>::iterator finder(nullptr);
        		return finder;
        	}
        	Node<Key,Value>* before=nullptr;
        	while(place!=nullptr)
        	{
        		before=place;
        		place=place->getRight();
        	}
        	splay(before);
        	typename splayTree<Key,Value>::iterator finder(before);
        	return finder;
        }
        //find the min leaf and then just remove it
        void deleteMinLeaf()
        {
        	Node<Key,Value>* place=this->mRoot;
        	if(place==nullptr) 
        	{
        		return;
        	}
        	Node<Key,Value>* before=nullptr;
        	//move down to far left 
        	while(place!=nullptr)
        	{
        		before=place;
        		place=place->getLeft();
        	}
        	//remove once we get to leftmost child
        	remove(before->getKey());
        }
        //find the max leaf and then simply remove it
        void deleteMaxLeaf()
        {
        	Node<Key,Value>* place=this->mRoot;
        	if(place==nullptr)
        	{
        		return;
        	}
        	//move down to far right
        	Node<Key,Value>* before=nullptr;
        	while(place!=nullptr)
        	{
        		before=place;
        		place=place->getRight();
        	}
        	//remove once we get to rightmost child
        	remove(before->getKey());
        }
    protected:
        void splay(Node<Key, Value> *r)
        {
        	//if the given node is null, do nothing and return
        	if (!r) return;
        	//grab the node's parent
        	Node<Key,Value>* parental=r->getParent();
        	//if nodes parent is null, then it is the root so 
        	//no need to splay
        	if(!parental) return;
        	//grab the nodes grandparent
        	Node<Key,Value>* grand=parental->getParent();
        	if(grand==nullptr)
        	{
        		
        	}

        }
};



