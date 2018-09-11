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

Item* LLSelectionSort(Item * head);
{
	Item* temp;
	Item* minimum;
	minimum=findMin(head);
	temp=minimum;
	
	if(head==nullptr)
	{
		return nullptr;
	}
	while (head->next!=nullptr)
	{	
		if (head->next->getValue()<head->getValue())
		{
			temp->prev->next=temp->next;
			temp->next->prev=temp->prev;
			minimum->prev=null;
			minimum->next=head;
			head=minimum;	
		}
	}
}

void swapper(Item* p, Item* n)
{
	Item* temp=p;
	temp->next->prevous=n;
	temp->previous->next=n
}