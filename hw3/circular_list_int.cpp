#include "circular_list_int.h"
#include <iostream>

CircularListInt::CircularListInt() {

}
CircularListInt::~CircularListInt() {
	//as long as head is not null
	while (!empty())
	{
		remove(count);
	}
	delete head; 
}


// Gets item at an index.
	// If an index is passed that is larger then the number of items in the list, it should "wrap around" back to the first element.
	// If there are no elements in the list, returns 0.
int CircularListInt:: get(size_t index) const
{
	//current now pointing to head
	Item* current=head;
	//edge case if empty, then return 0
	if(empty())
	{
		return 0;
	}
	//traverse through list until index
	for(size_t i=0;i<index;i++)
	{
		current=current->next;
	}
	//return value at index
	return current->value;
	
	return 0;
}

// returns true if the list is empty.
bool CircularListInt:: empty() const
{
	//if head == nullptr, then it is empty
	if(head==nullptr)
	{
		return true;
	}
	return false;
}
// get length of list.
 size_t CircularListInt:: size() const
{	
	//if empty, return 0 size==0
	if(empty()) return 0;
	//returns the count variable
	return count;

}
// Inserts (a copy of) the given item at the end of list.
void CircularListInt:: push_back(int value)
{
	Item * curr=head;
	//since we add, count increase
	count++;
	//we have a special case for when it was empty
	if(empty())
	{
		//create a new node with given value
		Item* newNode= new Item(value);
		//adjust pointers
		head=newNode;
		newNode->next=newNode;
		newNode->prev=newNode;
	
	}
	else
	{
		//traverse until we reach the end of the list
		//before it wraps around to head
		//with circular list, the last node next points
		//to head instead of null
		while(curr->next!=head)
		{
			curr=curr->next;
		}
		//once we reach the end, add node
		Item* insertion=new Item(value);
		//adjust pointers
		curr->next=insertion;
		insertion->prev=curr;
		insertion->next=head;
		head->prev=insertion;
		
	}

}
// Sets the item at the given index to have the given value.
// If an index is passed that is >= the number of items in the list, it should "wrap around" back to the first element.
void CircularListInt:: set(size_t index, int value)
{
	Item* curr=head;
	
	//traverse through list
	for(size_t i=0;i<index;i++)
	{
		curr=curr->next;
	}
	//once we reach node at index, set value
	curr->value=value;

}
// Finds the pointer to an item at the given index.
	// Handles wrapping the index around if it is ?= the size of the list.
	// Assumes that the size of the list is not 0.
 CircularListInt::Item * CircularListInt:: findItem(size_t index) const
 {
 	Item* current=head;
 	//traverse through list
 	for(size_t i=0;i<index;i++)
	{
		current=current->next;
	}
	//return pointer at index
	return current;
 }
// Removes the item at the given index from the list.
	// List elements after the removed element are pulled
	// forward, so their indicies decrease by one.
	// If an index is passed that is larger then the number of 
 	//items in the list, it should "wrap around" back to the first element.

 void CircularListInt:: remove(size_t index)
 {
 	// edge case, if it emoty, nothing
 	//to remove to return;
 	if(empty()) 
 	{
 		return;
 	}

 	Item* curr=head;
 	//size_t for length
	size_t length=size();
	//since we are removing, count decrements
	count--;
 	//if there is only one node, 
 	//then it is head so we just delete head
 	if(length==1)
 	{
 		delete head;
 		head=nullptr;
 		return;
 		
 	}
 	//if the index is greater than length
 	//adjust index by index%length
 	if(index>=length)
 	{
 		index=index%length;
 	}
	//traverse through list
	for(size_t i=0;i<index;i++)
 	{
 		curr=curr->next;
 	}
 	//if we are removing the head
 	if(index==0)
 	{
 		head=head->next;
 	}
 	//if we are not removing head 
 	//adjust pointers
 	else
 	{
	 	curr->prev->next=curr->next;
	 	curr->next->prev=curr->prev;
 	}
 	
 	//free up
 	delete *&curr;
 }
