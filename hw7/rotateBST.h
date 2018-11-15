#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>
#include "bst.h"


template <typename Key, typename Value>
class rotateBST: public BinarySearchTree {
    public:
        bool sameKeys(const rotateBST& t2) const;
        void transform(rotateBST& t2) const;
    protected:
        void leftRotate(Node<Key, Value>* r);
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
