#include "circular_list_int.h"
#include <iostream>

CircularListInt::~CircularListInt() {}

CircularListInt::CircularListInt() {

}
// Gets item at an index.
	// If an index is passed that is larger then the number of items in the list, it should "wrap around" back to the first element.
	// If there are no elements in the list, returns 0.
int CircularListInt:: get(size_t index) const
{
	Item* current=head;
	if(empty())
	{
		return 0;
	}
	for(size_t i=0;i<index;i++)
	{
		current=current->next;
	}
	return current->value;
	/*
	while (current->next!=head)
	{
		//if place is beyond index, wrap to beginning element
		if(place>index)
		{
			place=0;
		}
		if(place==index)
		{
			return (current->value);
		}
		place++;
		current=current->next;
	}
	*/
	return 0;
}

// returns true if the list is empty.
bool CircularListInt:: empty() const
{
	if(head==nullptr)
	{
		return true;
	}
	return false;
}
// get length of list.
 size_t CircularListInt:: size() const
{	
	return count;
	/*
	Item* runthrough=head;
	//while loop runs through the second to last item
	while(runthrough->next!=head)
	{
		count++;
	}
	//I add 1 more to count due to the fact that the while loop
	//only runs through the second to last item
	count+=1;
	return count;
	*/

}
// Inserts (a copy of) the given item at the end of list.
void CircularListInt:: push_back(int value)
{
	Item * curr=head;
	if(empty())
	{
		Item* newNode= new Item(value);
		head=newNode;
		newNode->next=newNode;
		newNode->prev=newNode;
		count++;
	}
	else
	{
		while(curr->next!=head)
		{
			curr=curr->next;
		}
		
		Item* insertion=new Item(value);
		curr->next=insertion;
		insertion->prev=curr;
		insertion->next=head;
		head->prev=insertion;
		count++;
	}

}
// Sets the item at the given index to have the given value.
// If an index is passed that is >= the number of items in the list, it should "wrap around" back to the first element.
void CircularListInt:: set(size_t index, int value)
{
	Item* curr=head;
	//int place=0;
	//int length=size();
	for(size_t i=0;i<index;i++)
	{
		curr=curr->next;
	}
	curr->value=value;

	/*
	while(curr->next!=head)
	{
		if (place>length-1)
		{
			place=0;
		}
		if(place==index)
		{
			curr->value=value;
		}
		place++;
	}
	*/
}
// Finds the pointer to an item at the given index.
	// Handles wrapping the index around if it is ?= the size of the list.
	// Assumes that the size of the list is not 0.
 Item * CircularListInt:: findItem(size_t index) const
 {
 	Item* current=head;
 	for(size_t i=0;i<index;i++)
	{
		current=current->next;
	}
	return &current;
 }
// Removes the item at the given index from the list.
	// List elements after the removed element are pulled forward, so their indicies decrease by one.
	// If an index is passed that is larger then the number of items in the list, it should "wrap around" back to the first element.

 void CircularListInt:: remove(size_t index)
 {
 
 	Item* curr=head;
 	//int place=(int)index;
	int length=size();
 	
 	if(length==1)
 	{
 		head->next=nullptr;
 		head->prev=nullptr;
 	}
 	/*
 	while(place>=length)
 	{
 		place=place-length;
 	}
 	*/
 	
	for(size_t i=0;i<index;i++)
 	{
 		curr=curr->next;
 	}
 	if(curr==head)
 	{
 		/*
 		curr->next->prev=curr->prev;
 		curr->prev->next=curr->next;
 		head->prev=nullptr;
 		head->next=nullptr;
 		head=head->next;
 		count--;
 		*/
 		head=curr->next;
 		head->prev=curr->prev;
 		curr->prev->next=head; 
 	}
 	else
 	{
	 
	 	curr->prev->next=curr->next;
	 	curr->next->prev=curr->prev;
	 	curr->next=nullptr;
	 	curr->prev=nullptr;
	 	count--;

 	}
 	/*
 	while(curr->next!=head)
 	{
 		if (place==index)
 		{
 			curr->next-previ
 		}
 		place++;
 	}
 	*/

 }