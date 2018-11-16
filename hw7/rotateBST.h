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
        void rrAll(Node<Key,Value>* root);
        void makethemEqual(Node<Key,Value>* ourRoot, Node<Key,Value>* c_root);
    protected:
        void leftRotate(Node<Key, Value>* c);
        void rightRotate(Node<Key, Value>* c);
};

template<typename Key, typename Value>
void rotateBST<Key,Value>::leftRotate(Node<Key,Value>* c)
{
    //when r has no children
    if(c->getRight()==NULL)
    {
        return;
    }
    //b is now pointing to c's right child
    Node<Key,Value>* b=c->getRight();
   if(c->getParent()!=NULL)
   {
       if(c->getKey()<c->getParent()->getKey())
       {
           c->getParent()->setLeft(b);
       }
       else
       {
           c->getParent()->setRight(b);
       }
   }
   else
   {
       this->mRoot=b;
   }
    c->setRight(b->getLeft());
    //if b has a left child meaning not null
    //then we set the parent pointer 
    //now pointing to b
    if(b->getLeft()!=NULL)
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
   if(c->getLeft()==NULL)
   {
       return;
   }
   Node<Key,Value>*b=c->getLeft();
   b->setParent(c->getParent());
   if(c->getParent()!=NULL)
   {
       if(c->getKey()<c->getParent()->getKey())
       {
           c->getParent();
       }
       else
       {
           c->getParent()->getRight(b);
       }
   }
   else
   {
       this->mRoot=b;
   }
   c->setLeft(b->getRight);
   if(b->getRight()!=NULL)
   {
       b->getRight()->setParent(c);
   }
   c->setParent(b);
   b->setRight(c);
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
    }
    t2.rrAll(root);
    //after rrALL is called, the root pointer
    //is pointing to null
    while(root!=this->mRoot)
    {
        t2.leftRotate(root);
        root=root->getParent();
    }
    Node<Key,Value>* correctLeft=this->mRoot->getLeft();
    Node<Key,Value>* correctRight=this->mRoot->getRight();
    t2.makethemEqual(t2.mRoot->getLeft(), correctLeft);
    t2.makethemEqual(t2.mRoot->getRight(),correctRight);
}


template<typename Key, typename Value>
void rotateBST<Key,Value>::rrAll(Node<Key,Value>* root)
{
   if(root==NULL) return;
   while(root->getLeft()!=NULL)
   {
       this->rightRotate(root);
       root=root->getParent();
   }
   rrAll(root->getRight());
}
template<typename Key, typename Value>
void rotateBST<Key,Value>::makethemEqual(Node<Key,Value>* ourRoot, Node<Key,Value>* c_root)
{
    if(ourRoot==NULL && c_root==NULL)
    {
        return;
    }
    if(ourRoot->getKey()<c_root->getKey())
    {
        while(ourRoot->getKey()!=c_root->getKey())
        {
            this->leftRotate(ourRoot);
            ourRoot=ourRoot->getParent();
        }
    }
    else if(ourRoot->getKey()>c_root->getKey())
    {
        while(ourRoot->getKey()!=c_root->getKey())
        {
            this->rightRotate(ourRoot);
            ourRoot=ourRoot->getParent();
        }
    }
    makethemEqual(ourRoot->getLeft(),c_root->getLeft());
    makethemEqual(ourRoot->getRight(),c_root->getRight());
}
