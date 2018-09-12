#include "circular_list_int.h"

// Gets item at an index.
	// If an index is passed that is larger then the number of items in the list, it should "wrap around" back to the first element.
	// If there are no elements in the list, returns 0.
int get(size_t index) const;
{
	int place=0;
	Item* current=head;

	while (current->next!=null)
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
	return 0;
}

// returns true iff the list is empty.
bool empty() const
{
	if(head==nullptr)
	{
		return true;
	}
	return false;
}
// Inserts (a copy of) the given item at the end of list.
void push_back(int value)
{
	bool empty=empty();
	if(empty)
	{
		Item* newNode= new Item;
		head=newNode;
		newNode->next=newNode;
		newNode->previous=newNode;
	}
	else
	{
		
	}

}


int main ()
{
	return 0;

}