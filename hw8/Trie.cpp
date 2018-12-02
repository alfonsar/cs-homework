#include "Trie.h"
#include <string>
#include <algorithm>
#include<stack>
#include<set>
#include <iostream>


TrieSet::TrieSet()
{
    //the constructor is to initialize the root
    TrieNode* ourRoot= new TrieNode;
    //set root to different letter
    ourRoot->letter='%';
    //root has no parent
    ourRoot->parent=NULL;
    //not a word
    ourRoot->inSet=0;
    //set root to this root
    root=ourRoot;
    //make babies
    produceOffSpring(ourRoot);
}


bool TrieSet::childrenExist(TrieNode* root)
{
    bool found=0;
    int alphabet=26;
    for(int i=0; i<alphabet; i++)
    {
        if(root->children[i])
        {
            found=1;
        }
    }
    return found;

}
void TrieSet::produceOffSpring(TrieNode* root)
{
    int counter=0;
    while(counter<27)
    {
        root->children[counter]=NULL;
        counter++;

    }
}
/* Add this string to the set.
Do nothing if the string is already in the set. */
void TrieSet::insert(std::string input)
{
    //make the input lowercase
    std::transform(input.begin(),input.end(),input.begin(),::tolower);
  	int len=input.length();
    //will create a pointer traverse through the tree
    TrieNode* trav=this->root;
    for(int i=0; i<len;i++)
    {
        //will grab the index of the input[i]
        int loc=input[i]-97;
        TrieNode* parental=trav;
        //will move the pointer to its children 
        //with corresponding letter location 
        trav=trav->children[loc];
        //if at a node that has a slash
        if(!trav)
        {
            TrieNode* newNode= new TrieNode;
            trav=newNode;
            //have the new node point to its parent
            trav->parent=parental;
            //will then allocate another 26 children 
            produceOffSpring(trav);
            //we change node's letter 
            trav->letter=input[i];
            
            parental->children[loc]=trav;
        }
       
    }
    //when we are all done, we set inSet to true
    //to show it is end of word
    trav->inSet=1;
}

void TrieSet::remove(std::string input)
{
    //will create a pointer traverse through the tree
    TrieNode* trav=prefix(input);
    if(!trav)
    {
        return;
    }
    //since we are deleting, set inSet to false
    trav->inSet=0;
    //if the node that we are at has no children,
    //we will deallocate all its children
    //then we set that node to '/'
    while(!childrenExist(trav) && trav->letter!='%'
        && trav->inSet==0)
    {
      	//grab the location of letter 
       	int loc=trav->letter-97;
        // //set a pointer to the parent of node 
        //we want to delete
        TrieNode* parental=trav->parent;
        //set the child to null
        parental->children[loc] = NULL;
        //delete the node
        delete trav;
        //now we move up
        trav=parental;
    }
}
TrieNode* TrieSet::prefix(std::string px) const
{
    //make the input lowercase
    std::transform(px.begin(),px.end(),px.begin(),::tolower);
    //will create a pointer traverse through the tree
    TrieNode* trav=root;
  	//grab the length of input
  	int len=px.length();
    for(int i=0; i<len;i++)
    {
        //will grab the index of the input[i]
        int loc=px[i]-97;
        //will travel to the location if children
        trav=trav->children[loc];
        //will traverse until 
        //we reach end of the word
        if(!trav)
        {
            //if we reach null, then that means
            //word does not exist and will return null
            return NULL;
        }
    }
    //return pointer to it
    return trav;
}
TrieSet::~TrieSet()
{
    clear(root);
}
void TrieSet::clear(TrieNode* button)
{
	//recursive call to delete all nodes
	//will be called in destructor
    //took from BST assignment 
	for(int i=0; i<alphabet; i++)
	{	
		if (button->children[i]) 
		{
			clear(button->children[i]);
		}
	}
	delete button;
}