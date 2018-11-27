#include "Trie.h"
#include <string>
#include <algorithm>

void TrieSet::makeChildren(TrieNode* root)
{
    for(int i=0; i<26; i++)
    {
        TrieNode* cNode= new TrieNode;
        cNode->inSet=false;
        cNode->letter='/';
        cNode->parent=root;
        root->children[i]=cNode;
    }
}
TrieSet::TrieSet()
{
    TrieNode* ourRoot= new TrieNode;
    ourRoot->inSet=false;
    ourRoot->letter='/';
    ourRoot->parent=NULL;

    root=ourRoot;
    makeChildren(ourRoot);
}
TrieSet::~TrieSet()
{

}
bool TrieSet:: hasChildren(TrieNode* root)
{
    for(int i=0; i<26; i++)
    {
        if(root->children[i]->letter!='/')
        {
            return true;
        }
    }
    return false;
}
/* Add this string to the set.
Do nothing if the string is already in the set. */
void TrieSet::insert(std::string input)
{
    //make the input lowercase
    std::transform(input.begin(),input.end(),input.begin(),::tolower);
    //will create a pointer traverse through the tree
    TrieNode* trav=root;
  
    for(int i=0; i<input.size();i++)
    {
        //will grab the index of the input[i]
        int loc=input[i]-97;
        //will move the pointer to its children 
        //with corresponding letter location 
        trav=trav->children[loc];
        //if at a node that has a slash
        if(trav->letter=='/')
        {
            //we change node's letter 
            trav->letter=input[i];
            //will then allocate another 26 children 
            makeChildren(trav);
        }
        else
        {
            //move onto next letter of input
            continue;
        }
    }
    //when we are all done, we set inSet to true
    //to show it is end of word
    trav->inSet=true;

}
void TrieSet::remove(std::string input)
{
    //make the input lowercase
    std::transform(input.begin(),input.end(),input.begin(),::tolower);
    //will create a pointer traverse through the tree
    TrieNode* trav=root;
  
    for(int i=0; i<input.size();i++)
    {
        //will grab the index of the input[i]
        int loc=input[i]-97;
        //will move the pointer to its children
        //with corresponsing letter location
        trav=trav->children[loc];
        //if its a slash, we return 
        //since there is already nothing there
        if(trav->letter=='/')
        {
            return;
        }
        else
        {
            continue;
        }
    }
    //since we are deleting, set inSet to false
    trav->inSet=false;
    //if the node that we are at has no children,
    //we will deallocate all its children
    //then we set that node to /
    if(!hasChildren(trav))
    {
        trav->letter='/';
        trav->inSet=false;
        for(int i=0; i<26; i++)
        {
            delete trav->children[i];
        }
        trav=trav->parent;
    }
}
TrieNode* TrieSet::prefix(std::string px)
{
    //make the input lowercase
    std::transform(px.begin(),px.end(),px.begin(),::tolower);
    //will create a pointer traverse through the tree
    TrieNode* trav=root;
  
    for(int i=0; i<px.size();i++)
    {
        //will grab the index of the input[i]
        int loc=px[i]-97;
        trav=trav->children[loc];
        if(trav->letter=='/')
        {
            return NULL;
        }
        else
        {
            continue;
        }
    }
    return trav;
}