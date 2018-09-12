#include "selection_sort.h"

// Given a list, returns a pointer to the smallest item.
// Returns nullptr if and only if head is nullptr.
Item* findMin(Item * head);

// Sorts the given list in ascending order and returns the new head.
// Returns nullptr iff head is nullptr.
Item* LLSelectionSort(Item * head);

Item* findMin(Item* head)
{
	Item* traverse=head->next;
	//will point to smallest value node
	Item* smallest;
	//variable to capture min
	int min=10000;
	if(head==nullptr)
	{
		return nullptr;
	}
	else
	{
		while(traverse!=nullptr)
		{
			if(traverse->getValue()<min)
			{
				min=traverse->getValue();
				smallest=traverse;
				traverse=traverse->next;
			}
			else
			{
				traverse=traverse->next;
			}

		}
		return smallest;
	}
	return nullptr;
}

Item* LLSelectionSort(Item * head)
{
	Item* order=head;
	Item* minimum;
	
	
	if(head==nullptr)
	{
		return nullptr;
	}
	while (order->next!=nullptr)
	{	
		minimum=findMin(order);
		if(minimum==order)
		{
			order=order->next;
			continue;
		}
		if(minimum->next!=nullptr)
		{
			minimum->next->prev=minimum->prev;
		
		}
			minimum->prev->next=minimum->next;

		if(order->prev!=nullptr)
		{
			order->prev->next=order->next;
			minimum->prev=order->prev;
		}
		else
		{
			head=minimum;
			minimum->prev=nullptr;
		}
		order->prev=minimum;
		minimum->next=order;
		
		
		/*
		minimum->prev=order->prev;
		minimum->prev->next=order->next;ygt
			order->next=minimum->next;
			
		
		if (head->next->getValue()<head->getValue())
		{
			temp->prev->next=temp->next;
			temp->next->prev=temp->prev;
			minimum->prev=null;
			minimum->next=head;
			head=minimum;	
		}
		*/
	}
	return order;
}

