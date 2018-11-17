#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>
#include <vector>
#include<algorithm>
#include "bst.h"


template <typename Key, typename Value>
class rotateBST: public BinarySearchTree<Key, Value>{
    public:
        //will check if the two trees have the same keys(nodes)
        bool sameKeys(const rotateBST& t2) const;
        //will perform the transformations
        //just as described by the homework instructions
        void transform(rotateBST& t2) const;
        //function used from lab that will make 
        //same keys function a lot easier
        void InOrder(std::vector<Key>& result, Node<Key,Value>* start)const; 
        //function to make right rotations until 
        //it looks like a linked list
        void rrAll(Node<Key,Value>* root);
        //Recursively do rotations on the left child and 
        //the right child until they match the node 
        //at that position of th-s->mRoot
        void makethemEqual(Node<Key,Value>* ourRoot, Node<Key,Value>* c_root);
    protected:
        //do a left rotation
        void leftRotate(Node<Key, Value>* c);
        //do a right rotation
        void rightRotate(Node<Key, Value>* c);
};

template<typename Key, typename Value>
void rotateBST<Key,Value>::leftRotate(Node<Key,Value>* c)
{
    //when r has no children
    if(!c->getRight())
    {
        return;
    }
    //b is now pointing to c's right child
    Node<Key,Value>* b=c->getRight();
    //for easier readablity, i made a pointer
    //pointing to c's parent
    Node<Key,Value>* cParental=c->getParent();
    b->setParent(c->getParent());
   //if c has a parent
   if(cParental)
   {
       //if c is the left child
       if(c->getKey()<cParental->getKey())
       {
           cParental->setLeft(b);
       }
       //if c is the right child
       else
       {
           cParental->setRight(b);
       }
   }
   //else if c has no parent, meaning its a root
   else
   {
       this->mRoot=b;
   }
    c->setRight(b->getLeft());
    //if b has a left child meaning not null
    //then we set the parent pointer 
    //now pointing to b
    if(b->getLeft())
    {
        b->getLeft()->setParent(c);
    }
    //now adjust pointer to make c's
    //parent b
    c->setParent(b);
    b->setLeft(c);
}
template<typename Key, typename Value>
void rotateBST<Key,Value>::rightRotate(Node<Key,Value>* c)
{
   //if c has no left child, do nothing 
   if(!c->getLeft())
   {
       return;
   }
   Node<Key,Value>*b=c->getLeft();
   Node<Key,Value>* cParental=c->getParent();
   b->setParent(c->getParent());
   //if c has a parent
   if(cParental)
   {
      //if c is left child
       if(c->getKey()<cParental->getKey())
       {
           cParental->setLeft(b);
       }
       //or if c is right child
       else
       {
           cParental->setRight(b);
       }
   }
   //if c has no parent so it was the root
   else
   {
       this->mRoot=b;
   }
   c->setLeft(b->getRight());
   //adjust pointers
   if(b->getRight())
   {
       b->getRight()->setParent(c);
   }
   c->setParent(b);
   b->setRight(c);
}
//grabbed from previous lab (lab11)
template<typename Key, typename Value>
void rotateBST<Key,Value>::InOrder(std::vector<Key>& result, Node<Key,Value>* start) const
{

    if(start->getLeft()) {
        InOrder(result, start->getLeft());
    }
      result.push_back(start->getKey());
    if(start->getRight()) {
        InOrder(result, start->getRight());
    }
}

template<typename Key, typename Value>
bool rotateBST<Key,Value>::sameKeys(const rotateBST& t2) const
{
	//create two vectors that will push node values and 
	//then we will compare
	std::vector<Key> first;
	std::vector<Key> second;
	InOrder(first,this->mRoot);
	InOrder(second,t2.mRoot);
	// if equal, then true
	if(first==second)
	{
		return true;
	}
	return false;
}
template<typename Key, typename Value>
void rotateBST<Key,Value>::transform(rotateBST& t2) const
{
	if(sameKeys(t2)==0)
    {
        return;
    }
 
    //we now do a right rotation until 
    //we make it look like a linked list
    t2.rrAll(t2.mRoot);
    Node<Key,Value>* c_root=this->mRoot;
    Node<Key,Value>* ourRoot=t2.mRoot;
   	//now we keep doing left rotations on the root
   	//until our desirable node is the root
    while(ourRoot->getKey()!=c_root->getKey())
    {
    	t2.leftRotate(ourRoot);
    	ourRoot=ourRoot->getParent();
    }
    //assign the correct left and correct right 
    //that we want our root's left child and right
    //child to be 
    Node<Key,Value>* correctLeft=this->mRoot->getLeft();
    Node<Key,Value>* correctRight=this->mRoot->getRight();
    t2.makethemEqual(t2.mRoot->getLeft(),correctLeft);
    t2.makethemEqual(t2.mRoot->getRight(),correctRight);
}


template<typename Key, typename Value>
void rotateBST<Key,Value>::rrAll(Node<Key,Value>* root)
{
   if(!root) return;
   //if there is a left child, we rotate the node that has the left child
   while(root->getLeft())
   {
       this->rightRotate(root);
       //after we rotate, we move the root pointer up 
       root=root->getParent();
   }
   rrAll(root->getRight());
}
//function that does number 5 for how transform should work
//that is found in homework instructions
template<typename Key, typename Value>
void rotateBST<Key,Value>::makethemEqual(Node<Key,Value>* ourRoot, Node<Key,Value>* c_root)
{
    //if both are null, return
    if(!ourRoot && !c_root)
    {
        return;
    }
    //if t2 root is less, do a left rotation
    if(ourRoot->getKey()<c_root->getKey())
    {
        while(ourRoot->getKey()!=c_root->getKey())
        {
            //here we do the left rotation
            this->leftRotate(ourRoot);
            //we move the ourRoot pointer up one
            ourRoot=ourRoot->getParent();
        }
    }
   //if t2 root is greater, we do a right rotation
    else if(ourRoot->getKey()>c_root->getKey())
    {
        while(ourRoot->getKey()!=c_root->getKey())
        {
            //do a right rotation
            this->rightRotate(ourRoot);
            //move ourRoot pointer up one
            ourRoot=ourRoot->getParent();
        }
    }
    makethemEqual(ourRoot->getLeft(),c_root->getLeft());
    makethemEqual(ourRoot->getRight(),c_root->getRight());
}
