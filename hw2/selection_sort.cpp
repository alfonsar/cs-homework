#include "selection_sort.h"

// Given a list, returns a pointer to the smallest item.
// Returns nullptr if and only if head is nullptr.
Item* findMin(Item * head);

// Sorts the given list in ascending order and returns the new head.
// Returns nullptr iff head is nullptr.
Item* LLSelectionSort(Item * head);


// Given a list, returns a pointer to the smallest item.
// Returns nullptr if and only if head is nullptr.
Item* findMin(Item* head)
{
	Item* traverse=head->next;
	//will point to smallest value node
	Item* smallest;
	//variable to capture min
	int min=100000;
	//case for when linked list is empty
	if(head==nullptr)
	{
		return nullptr;
	}
	else
	{
		//while traverse(head->next) is not null
		while(traverse!=nullptr)
		{
			//if we find that the value at traverse is less than min
			//set min equal to value at travers
			if(traverse->getValue()<min)
			{
				min=traverse->getValue();
				//have smallest pointing to the location traverse
				smallest=traverse;
				//we move along the list
				traverse=traverse->next;
			}
			else
			{
				//else move along linked list
				//like normal
				traverse=traverse->next;
			}

		}
		//return pointer pointing to smallest element
		return smallest;
	}
	return nullptr;
}
// Sorts the given list in ascending order and returns the new head.
// Returns nullptr iff head is nullptr.
Item* LLSelectionSort(Item * head)
{
	Item* order=head;
	Item* minimum;
	//if list is empty, then retull null
	if(head==nullptr)
	{
		return nullptr;
	}
	minimum=findMin(order);
	//if minimum is pointing at head
	if(minimum==order)
	{
		order=order->next;
	}
	//if not empty, then we sort
	else
	{
		while (order->next!=nullptr)
		{	
			//use findmin to find smallest element in linkedlist
			minimum=findMin(order);
			
			if(minimum->next!=nullptr)
			{
				minimum->next->prev=minimum->prev;
			}
			minimum->prev->next=minimum->next;
			if(order->prev!=nullptr)
			{
				order->prev->next=minimum;
				minimum->prev=order->prev;
			}
			else
			{
				head=minimum;
				minimum->prev=nullptr;
			}
			order->prev=minimum;
			minimum->next=order;
			}
	}
	return head;
}