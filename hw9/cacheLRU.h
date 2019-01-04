#include "splayTree.h"
#include <utility>
#include "print_bst.h"

template<typename Key, typename Value>
class cacheLRU: public splayTree<Key,Value>{
	public:
		cacheLRU(int capacity)
		{
			cap=capacity;
			size=0;
		}
		~cacheLRU()
		{

		}
		void put(const std::pair<const Key, Value>& keyValuePair)
		{
			//create a variable to store the key 
			Key key=keyValuePair.first;
			//use the internal find function to find the key.
			//since the function returns a pointer, if it is null, then the 
			//key is not already in there so we add it
			if(BinarySearchTree<Key,Value>::internalFind(key)==nullptr)
			{
				//if we reach capactiy, we must remove the minleaf node
				if(size>=cap)
				{
					//delete min leaf
					splayTree<Key,Value>::deleteMinLeaf();

					//decrement size
					size--;
				}
				//call the insert function from splay
				splayTree<Key,Value>::insert(keyValuePair);
				//increase size
				size++;
			}
			
		}
		std::pair<const Key, Value> get(const Key& key)
		{
			splayTree<Key,Value>::find(key);
			Node<Key,Value>* lookup= BinarySearchTree<Key,Value>::internalFind(key);
			if(lookup==nullptr)
			{
				throw std::logic_error("Error!");
			}
			else
			{
				return std::make_pair(lookup->getKey(),lookup->getValue());
			}
		}
	private:
		//the capacity of the cache
		int cap;
		//the actual size of the cache at a particular moment
		int size;
};