#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <cstdlib>
#include <string>
#include<cmath>
#include "rotateBST.h"

/**
* A special kind of node for an AVL tree, which adds the height as a data member, plus 
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
	// Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int getHeight() const;
    void setHeight(int height);

    // Getters for parent, left, and right. These need to be redefined since they 
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int mHeight;
};

/*
--------------------------------------------
Begin implementations for the AVLNode class.
--------------------------------------------
*/

/**
* Constructor for an AVLNode. Nodes are initialized with a height of 0.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent)
    : Node<Key, Value>(key, value, parent)
    , mHeight(0)
{

}

/**
* Destructor.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* Getter function for the height. 
*/
template<typename Key, typename Value>
int AVLNode<Key, Value>::getHeight() const
{
    return mHeight;
}

/**
* Setter function for the height. 
*/
template<typename Key, typename Value>
void AVLNode<Key, Value>::setHeight(int height)
{
    mHeight = height;
}

/**
* Getter function for the parent. Used since the node inherits from a base node.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key,Value>*>(this->mParent);
}

/**
* Getter function for the left child. Used since the node inherits from a base node.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key,Value>*>(this->mLeft);
}

/**
* Getter function for the right child. Used since the node inherits from a base node.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key,Value>*>(this->mRight);
}

/*
------------------------------------------
End implementations for the AVLNode class.
------------------------------------------
*/

/**
* A templated balanced binary search tree implemented as an AVL tree.
*/
template <class Key, class Value>
class AVLTree : public rotateBST<Key, Value>
{
public:
	// Methods for inserting/removing elements from the tree. You must implement
	// both of these methods. 
    virtual void insert(const std::pair<Key, Value>& keyValuePair) override;
    void remove(const Key& key);

private:
	/* Helper functions are strongly encouraged to help separate the problem
	   into smaller pieces. You should not need additional data members. */
};

/*
--------------------------------------------
Begin implementations for the AVLTree class.
--------------------------------------------
*/

/**
* Insert function for a key value pair. Finds location to insert the node and then balances the tree. 
*/
template<typename Key, typename Value>
void AVLTree<Key, Value>::insert(const std::pair<Key, Value>& keyValuePair)
{
    //if tree is empty, change the root node from null 
    // to input parameter key and value

    if(this->mRoot==NULL)
    {
        AVLNode<Key,Value>* another=new AVLNode<Key,Value>(keyValuePair.first, keyValuePair.second, NULL);   
        this->mRoot=another;
        return;
    }
    //if duplicate entry, overwrite with new value
    Node<Key,Value>* checker;
    checker=this->internalFind(keyValuePair.first);
    AVLNode<Key,Value>* node= dynamic_cast<AVLNode<Key,Value>*>(checker);
   if(!node)
   {
       node->setValue(keyValuePair.second);
       return;
   }
    //if there isn't a duplicate set node point to root
    node=this->mRoot;
    while(node!=NULL)
    {
        if(keyValuePair.first<node->getKey())
        {
            if(node->getLeft()==NULL)
            {
                AVLNode<Key,Value>* another=new AVLNode<Key,Value>(keyValuePair.first,keyValuePair.second,NULL);
                node->setLeft(another);
                break;
            }
            else
            {
                node=node->getLeft();
            }
        }
        else
        {
            if(node->getRight()==NULL)
            {
                AVLNode<Key,Value>* another=new AVLNode<Key,Value>(keyValuePair.first,keyValuePair.second,NULL);
                node->setRight(another);
                break;
            }
            else
            {
                node=node->getRight();
            }
        }
    }
    //now time to check for balance
    AVLNode<Key,Value>* unbalanced=internalFind(node->getKey());
    //uB stands for unbalanced 
    bool uB=false;
    while(!uB)
    {
        //will be checking if node is unbalanced 
        if(unbalanced->getLeft()==NULL || unbalanced->getRight()==NULL)
        {
            if(unbalanced->getLeft()==NULL && unbalanced->getRight()!=NULL)
            {
                //if left is null, we will consider the height as 0
                //so if the right side is not null and bigger than 1
                //we know that it is unbalanced
                if(abs(unbalanced->getRight()->getHeight())>1)
                {
                    uB=true;
                }
            }
            //now if right was null but left child is not null
            else if(unbalanced->getRight()==NULL && unbalanced->getLeft()!=NULL)
            {
                if(abs(unbalanced->getLeft()->getHeight()>1))
                {
                    uB=true;
                }
            }
            //if is it leaf node, then it has no left or right subtree
            else
            {
                unbalanced=unbalanced->getParent();
            }
        }
        //if the node has two children, then we do regular abs value difference
        else if(abs(unbalanced->getLeft()->getHeight() - unbalanced->getRight()->getHeight())>1) 
        {
            uB=true;
        }
        //if they are balanced, we traverse up to root 
        else
        {
            unbalanced->setHeight(unbalanced->getHeight()+1);
            unbalanced=unbalanced->getParent();
        }
    }
    //if we find an unbalanced tree, we now do rotations to 
    //balance the tree once again
    if(uB)
    {
        AVLNode<Key,Value>* nZ=unbalanced;
        if(unbalanced->getLeft()->getHeight() < unbalanced->getRight()->getHeight())
        {
            AVLNode<Key,Value> nY=unbalanced->getRight();
            if(nY->getLeft()->getHeight()==nY->getRight()->getHeight())
            {
                //r zigzig
                this->leftRotate(nZ);
                //now we gotta update the height
                nZ->setHeight(nZ->getHeight()-2);
            }
            //right heavier than left is heavier
            else if(nY->getLeft()->getHeight()< nY->getRight()->getHeight())
            {
                
                AVLNode<Key,Value> nX=unbalanced->getLeft();
                //right rotate on , then left rotate on z
                this->rightRotate(nY);
                this->leftRotate(nZ);
                //now that we have rotated
                //we fix the heights
                nX->setHeight(nX->getHeight()+1);
                nY->setHeight(nY->getHeight()-1);
                nZ->setHeight(nZ->getHeight()-2);
            }
            //right right 
            else
            {
                this->leftRotate(nZ);
                nZ->setHeight(nZ->getHeight()-2);
            }

        }
        else
        {
            AVLNode<Key,Value>* nY=unbalanced->getLeft();
            AVLNode<Key,Value>* nX=nY->getRight(); //check this !!!!!!!!!
            if(nY->getLeft()->getHeight()==nY->getRight()->getHeight())
            {
                //zig-zig
                this->rightRotate(nZ);
                nZ->setHeight(nZ->getHeight()-2);
            }
            else if(nY->getLeft()->getHeight()<nY->getRight()->getHeight())
            {
                //left rotate on y, then right rotate on z
                this->leftRotate(nY);
                this->rightRotate(nZ);
                //adjust height
                nX->setHeight(nX->getHeight()+1); //check THIS!!!!!
                nY->setHeight(nY->getHeight()-1);
                nZ->setHeight(nZ->getHeight()-2);
            }
            else
            {
                this->rightRotate(nZ);
                nZ->setHeight(nZ->getHeight()-2);
            }
        }
    }

}

/**
* Remove function for a given key. Finds the node, reattaches pointers, and then balances when finished. 
*/
template<typename Key, typename Value>
void AVLTree<Key, Value>::remove(const Key& key)
{
   
}

/*
------------------------------------------
End implementations for the AVLTree class.
------------------------------------------
*/

#endif
