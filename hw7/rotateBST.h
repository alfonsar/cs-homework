#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>
#include <vector>
#include "bst.h"


template <typename Key, typename Value>
class rotateBST: public BinarySearchTree<Key, Value>{
    public:
        bool sameKeys(const rotateBST& t2) const;
        void transform(rotateBST& t2) const;
        void InOrder(std::vector<int>& result, Node<Key,Value>* start); 
        void recursive(Node<Key,Value>* root);
    protected:
        void leftRotate(Node<Key, Value>* c);
        void rightRotate(Node<Key, Value>* c);
};

template<typename Key, typename Value>
void rotateBST<Key,Value>::leftRotate(Node<Key,Value>* c)
{
   bool root;
   bool child;
    //when r has no children
    if(c->getRight()==NULL)
    {
        return;
    }
    Node<Key,Value>* b=c->getRight();
    Node<Key,Value>* t2= b->getLeft();
    b->setLeft(c);
    if(root)
    {
        b->setParent(NULL);
    }
    else if (!root)
    {
        b->setParent(c->getParent());
        if(child)
        {
            b->getParent()->setLeft(c);
        }
        else if(!child)
        {
            c->getParent()->setRight(b);
        }
    }
    c->setParent(b);
    if(t2!=NULL)
    {
        t2->setParent(c);
        c->setRight(t2);
    }
  
}
template<typename Key, typename Value>
void rotateBST<Key,Value>::rightRotate(Node<Key,Value>* c)
{
   bool root;
   bool child;
    //if c has no left child, then it should do nothing
    if(c->getLeft==NULL)
    {
        return;
    }
    if(c->getParent()==NULL)
    {
        root=true;
    }
    else if(c->getKey()<c->getParent()->getKey())
    {
        child=true;
    }
    Node<Key,Value>* b=c->getLeft();
    Node<Key,Value>* t2=b->getRight();
    //working on b node
    b->setRight(c);
    if(root)
    {
        b->setParent(NULL);
    }
    else
    {
        b->setParent(c->getParent());
        if(child)
        {
            b->getParent()->setRight(b);
        }
        else{
            c->getParent()->setRight(b);
        }
    }
    //working on c node
    c->setParent(b);
    if(t2!=NULL)
    {
        t2->setParent(c);
        c->setLeft(t2);
    }
}
template<typename Key, typename Value>
void rotateBST<Key,Value>::InOrder(std::vector<int>& result, Node<Key,Value>* start) 
{

    if(start->left != nullptr) {
        InOrder(result, start->left);
    }
      result.push_back(start->val);
    if(start->right != nullptr) {
        InOrder(result, start->right);
    }
}

template<typename Key, typename Value>
bool rotateBST<Key,Value>::sameKeys(const rotateBST& t2) const
{
	std::vector<Key> first;
	std::vector<Key> second;
	Inorder(first,this->mRoot);
	Inorder(second,t2.mRoot);
	if(first==second)
	{
		return true;
	}
	return false;
}
template<typename Key, typename Value>
void rotateBST<Key,Value>::transform(rotateBST& t2) const
{
	if(!sameKeys(t2))
    {
        return;
    }
    Node<Key,Value>* root=t2.mRoot;
    //right rotation

    while(root->getLeft()!=NULL)
    {
        t2.rightRotate(root);
        root=root->getParent();
        if(root->getLeft()==NULL && root->getRight()!=NULL)
        {
            root=root->getRight();
        }
        else if(root->getLeft()==NULL && root->getRight()==NULL)
        {
            break;
        }
    }
    while(root->getParent()!=NULL)
    {
        root=root->getParent();
    }
    while(this->mRoot->getKey()!=root->getKey())
    {
        t2.leftRotate(root);
        root=root->getParent();
    }
}
template<typename Key, typename Value>
void rotateBST<Key,Value>::recursive(Node<Key,Value>* root)
{
    
}
