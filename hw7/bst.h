#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/**
* A templated class for a Node in a search tree. The getters for parent/left/right are virtual so that they
* can be overridden for future kinds of search trees, such as Red Black trees, Splay trees, and AVL trees.
*/
template <typename Key, typename Value>
class Node
{
public:
	Node(const Key& key, const Value& value, Node<Key, Value>* parent);
	virtual ~Node();

	const std::pair<Key, Value>& getItem() const;
	std::pair<Key, Value>& getItem();
	const Key& getKey() const;
	const Value& getValue() const;
	Key& getKey();
	Value& getValue();

	virtual Node<Key, Value>* getParent() const;
	virtual Node<Key, Value>* getLeft() const;
	virtual Node<Key, Value>* getRight() const;

	void setParent(Node<Key, Value>* parent);
	void setLeft(Node<Key, Value>* left);
	void setRight(Node<Key, Value>* right);
	void setValue(const Value &value);

protected:
	std::pair<Key, Value> mItem;
	Node<Key, Value>* mParent;
	Node<Key, Value>* mLeft;
	Node<Key, Value>* mRight;
};

/*
	-----------------------------------------
	Begin implementations for the Node class.
	-----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent)
	: mItem(key, value)
	, mParent(parent)
	, mLeft(NULL)
	, mRight(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed within the deleteAll() helper method in the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<Key, Value>& Node<Key, Value>::getItem() const
{
	return mItem;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<Key, Value>& Node<Key, Value>::getItem()
{
	return mItem;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
	return mItem.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
	return mItem.second;
}

/**
* A non-const getter for the key.
*/
template<typename Key, typename Value>
Key& Node<Key, Value>::getKey()
{
	return mItem.first;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
	return mItem.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
	return mParent;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
	return mLeft;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
	return mRight;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
	mParent = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
	mLeft = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
	mRight = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
	mItem.second = value;
}

/*
	---------------------------------------
	End implementations for the Node class.
	---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
	public:
		BinarySearchTree(); //TODO
		virtual ~BinarySearchTree(); //TODO
  		virtual void insert(const std::pair<Key, Value>& keyValuePair); //TODO
        virtual void remove(const Key& key); //TODO
  		void clear(); //TODO
  		void print() const;
  		bool isBalanced() const; //TODO
		int height(Node<Key,Value>* root) const;
		void help_clear(Node<Key,Value>* root);

	public:
		/**
		* An internal iterator class for traversing the contents of the BST.
		*/
		class iterator
		{
			public:
				iterator(Node<Key,Value>* ptr);
				iterator();

				std::pair<Key,Value>& operator*() const;
				std::pair<Key,Value>* operator->() const;

				bool operator==(const iterator& rhs) const;
				bool operator!=(const iterator& rhs) const;
				iterator& operator=(const iterator& rhs);

				iterator& operator++();

			protected:
				Node<Key, Value>* mCurrent;

				friend class BinarySearchTree<Key, Value>;
		};

	public:
		iterator begin() const;
		iterator end() const;
		iterator find(const Key& key) const;

	protected:
		Node<Key, Value>* internalFind(const Key& key) const; //TODO
		Node<Key, Value>* getSmallestNode() const; //TODO
		void printRoot (Node<Key, Value>* root) const;

	protected:
		Node<Key, Value>* mRoot;

	public:
		void print() {this->printRoot(this->mRoot);}

};

/*
	---------------------------------------------------------------
	Begin implementations for the BinarySearchTree::iterator class.
	---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<typename Key, typename Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value>* ptr)
	: mCurrent(ptr)
{

}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<typename Key, typename Value>
BinarySearchTree<Key, Value>::iterator::iterator()
	: mCurrent(NULL)
{

}

/**
* Provides access to the item.
*/
template<typename Key, typename Value>
std::pair<Key, Value>& BinarySearchTree<Key, Value>::iterator::operator*() const
{
	return mCurrent->getItem();
}

/**
* Provides access to the address of the item.
*/
template<typename Key, typename Value>
std::pair<Key, Value>* BinarySearchTree<Key, Value>::iterator::operator->() const
{
	return &(mCurrent->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::iterator::operator==(const BinarySearchTree<Key, Value>::iterator& rhs) const
{
	return this->mCurrent == rhs.mCurrent;
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::iterator::operator!=(const BinarySearchTree<Key, Value>::iterator& rhs) const
{
	return this->mCurrent != rhs.mCurrent;
}

/**
* Sets one iterator equal to another iterator.
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator &BinarySearchTree<Key, Value>::iterator::operator=(const BinarySearchTree<Key, Value>::iterator& rhs)
{
	this->mCurrent = rhs.mCurrent;
	return *this;
}

/**
* Advances the iterator's location using an in-order traversal.
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator& BinarySearchTree<Key, Value>::iterator::operator++()
{
	if(mCurrent->getRight() != NULL)
	{
		mCurrent = mCurrent->getRight();
		while(mCurrent->getLeft() != NULL)
		{
			mCurrent = mCurrent->getLeft();
		}
	}
	else if(mCurrent->getRight() == NULL)
	{
		Node<Key, Value>* parent = mCurrent->getParent();
		while(parent != NULL && mCurrent == parent->getRight())
		{
			mCurrent = parent;
			parent = parent->getParent();
		}
		mCurrent = parent;
	}
	return *this;
}

/*
	-------------------------------------------------------------
	End implementations for the BinarySearchTree::iterator class.
	-------------------------------------------------------------
*/

/*
	-----------------------------------------------------
	Begin implementations for the BinarySearchTree class.
	-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<typename Key, typename Value>
BinarySearchTree<Key, Value>::BinarySearchTree()
{
	mRoot=NULL;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
	clear();
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
	printRoot(mRoot);
	std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::begin() const
{
	BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
	return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::end() const
{
	BinarySearchTree<Key, Value>::iterator end(NULL);
	return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::find(const Key& key) const
{
	Node<Key, Value>* curr = internalFind(key);
	BinarySearchTree<Key, Value>::iterator it(curr);
	return it;
}

/**
* An insert method to insert into a Binary Search Tree. The tree will not remain balanced when
* inserting.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<Key, Value>& keyValuePair)
{
	//if the tree is empty, change the root node from null
	//to input parameter key and value
	if(mRoot==NULL)
	{
		mRoot= new Node<Key, Value>(keyValuePair.first, keyValuePair.second,NULL);
		return;
	}

	Node<Key, Value>* node = internalFind(keyValuePair.first);
	if(node!=NULL)
	{
		node->setValue(keyValuePair.second);
		return;
	}
	node=mRoot;
	while(node!=NULL)
	{
		if((keyValuePair.first < node->getKey()))
		{
			if(node->getLeft()==NULL)
			{
				Node<Key, Value>* another= new Node<Key,Value>(keyValuePair.first, keyValuePair.second,node);
				node->setLeft(another);
				return;
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
				Node<Key,Value>* another= new Node<Key,Value>(keyValuePair.first,keyValuePair.second,node);
				node->setRight(another);
				return;
			}
			else
			{
				node=node->getRight();
			}
		}
	}

}

/**
* An remove method to remove a specific key from a Binary Search Tree. The tree may not remain balanced after
* removal.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
	Node<Key,Value>* node=internalFind(key);
	if(node==NULL)
	{
		return;
	}
	if(node->getParent()==NULL && node->getLeft()==NULL && node->getRight()==NULL)
	{
		mRoot=NULL;
		delete node;
		return;
	}
	if(node==mRoot)
	{
		
		if(node->getRight()!=NULL && node->getLeft()!=NULL)
		{
			Node<Key,Value>* pre=node->getLeft();
			while(pre->getRight()!=NULL)
			{
				pre=pre->getRight();
			}
			pre->setRight(node->getRight());
			node->getRight()->setParent(pre);	
			pre->setParent(NULL);
			mRoot = pre;
			delete node;
			return;
		}
		 else if (node->getRight()==NULL || node->getLeft()==NULL)
		 {
		 	if(node->getLeft()==NULL)
		 	{
		 		Node<Key,Value>* suc=node->getRight();
		 		suc->setParent(NULL);
		 		node->setRight(NULL);
		 		mRoot=suc;
		 		delete node;
		 		return;
		 	}
		 	else if(node->getRight()==NULL)
		 	{
		 		Node<Key,Value>* pre=node->getLeft();
		 		while(pre->getRight()!=NULL)
		 		{
		 			pre=pre->getRight();
		 		}
		 		pre->setParent(NULL);
		 		node->setLeft(NULL);
		 		mRoot=pre;
		 		delete node;
		 		return;
		 	}
		 }
	}
	//if a leaf node, then you just have the parent of it point to NULL
	else if(node->getLeft()==NULL && node->getRight()==NULL)
	{
		Node<Key,Value>* parental=node->getParent();
		//if(parental->getLeft()->getKey()==key)
		if(node->getKey()<parental->getKey())
		{
			parental->setLeft(NULL);
			delete node;
			return;
		}
		//else if(parental->getRight()->getKey()==key)
		else if(node->getKey()>parental->getKey())
		{
			parental->setRight(NULL);
			delete node;
			return;
		}
	}
	//if the node has one child
	else if(node->getRight()==NULL || node->getLeft()==NULL)
	{
		if(node->getRight()==NULL)
		{
			Node<Key,Value>* parental=node->getParent();
			if(parental->getKey()<node->getKey())
			{
				parental->setRight(node->getLeft());
				node->getLeft()->setParent(node->getParent());
				delete node;
				return;
			}
			else{
				parental->setLeft(node->getLeft());
				node->getLeft()->setParent(node->getParent());
				delete node;
				return;

			}
		}
		else if(node->getLeft()==NULL)
		{
			Node<Key,Value>*parental=node->getParent();
			if(parental->getKey()<node->getKey())
			{
				parental->setRight(node->getRight());
				node->getRight()->setParent(node->getParent());
				delete node;
				return;
			}
			else
			{
				parental->setLeft(node->getRight());
				node->getRight()->setParent(node->getParent());
				delete node;
				return;			
			}
		}
	}
	//if the node has two children
	else if(node->getRight()!=NULL && node->getLeft()!=NULL)
	{
		Node<Key,Value>* pre=node->getLeft();
		if(pre->getRight()==NULL)
		{
			Node<Key,Value>* parental=node->getParent();
			if(pre->getRight()==NULL) //pre->getLeft==NULL && 
			{
				//if node being removed is greater than parent(right)
				if(parental->getKey()<node->getKey())
				{
					parental->setRight(pre);
					pre->setParent(parental);
					pre->setRight(node->getRight());
					node->getRight()->setParent(pre);
					delete node;
					return;
				}
				//if node being removd is smaller than parent (left)
				else
				{
					parental->setLeft(pre);
					pre->setParent(parental);
					pre->getRight()->setParent(pre);
					delete node;
					return;
				}
			}
		}
		//to find predecessor, you go once to the left child
		//then continue onto the rightmost child
		while(pre->getRight()!=NULL)
		{
			pre=pre->getRight();
		}

		//again node is greater than parent (right)
		if(node->getKey()>node->getParent()->getKey())
		{
			if(pre->getLeft()!=NULL)
			{
				pre->getParent()->setRight(pre->getLeft());
				pre->getLeft()->setParent(pre->getParent());
			}
			else
			{
				pre->getParent()->setRight(NULL);
			}
			node->getParent()->setRight(pre);
			pre->setParent(node->getParent());
			pre->setRight(node->getRight());
			pre->setLeft(node->getLeft());
			pre->getLeft()->setParent(pre);
			pre->getRight()->setParent(pre);
			delete node;
			return;
		}
		//again node is less than parent (left)
		else
		{
			if(pre->getLeft()!=NULL)
			{
				pre->getParent()->setRight(pre->getLeft());
				pre->getLeft()->setParent(pre->getParent());
			}
			else
			{
				pre->getParent()->setRight(NULL);
			}
			node->getParent()->setLeft(pre);
			pre->setParent(node->getParent());
			pre->setRight(node->getRight());
			pre->setLeft(node->getLeft());
			pre->getLeft()->setParent(pre);
			pre->getRight()->setParent(pre);
			delete node;
			return;
		}
		
	}
	return;

}

/**
* A method to remove all contents of the tree and reset the values in the tree
* for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
	help_clear(mRoot);
}
template<typename Key, typename Value>
void BinarySearchTree<Key,Value>::help_clear(Node<Key,Value>* root)
{
	if(root!=NULL)
	{
		help_clear(root->getLeft());
		help_clear(root->getRight());
		remove(root->getKey());
	}
}

/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::getSmallestNode() const
{
	Node<Key,Value>* c_node=mRoot;
	while(c_node->getLeft())
	{
		c_node=c_node->getLeft();
	}
	return c_node;
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
	Node<Key, Value>* c_node=mRoot;
	while(c_node!=NULL)
	{
		if(c_node->getKey()==key)
		{
			return c_node;
		}
		else if(key<c_node->getKey())
		{
			c_node=c_node->getLeft();
		}
		else if(key>c_node->getKey())
		{
			c_node=c_node->getRight();
		}
	}
	return NULL;
}
template<typename Key, typename Value>
int BinarySearchTree<Key,Value>::height(Node<Key,Value>* root) const
{
	if (root == nullptr) return 0;

	int l = height(root->getLeft());
	int r = height(root->getRight());
	if (l == -1 || r == -1) return -1;
	int comp = abs(l - r);
	if (comp > 1) return -1;
	else return std::max(l, r) + 1;
}
/**
 * Return true iff the BST is an AVL Tree.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
	int hight = height(mRoot);
	if (hight == -1) return false;
	return true;
}


/**
 * Lastly, we are providing you with a print function, BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->mRoot)

   It will print up to 5 levels of the tree rooted at the passed node, in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
	---------------------------------------------------
	End implementations for the BinarySearchTree class.
	---------------------------------------------------
*/

#endif
