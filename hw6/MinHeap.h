#include<vector>
#include<stdexcept>
template <class T>
class MinHeap 
{
  public:
    /* Constructor that builds a d-ary Min Heap
    This should work for any d >= 2,
    but doesn't have to do anything for smaller d.*/
    MinHeap (int d)
    {
      arry=d;
    }
    ~MinHeap () {
      
    }
    /* adds the item to the heap, with the given priority. */
    void add (T item, int priority)
    {
      std::pair<T,int> add(item, priority);
      items.push_back(add);
      heapUp();
    }
    /* returns the element with smallest priority.  
    Break ties however you wish.  
    Throws an exception if the heap is empty. */
    const T & peek () const
    {
      if(items.empty())
      {
        throw std::out_of_range("Error: Heap is empty");
      }
      return items[0].first;
    }
    /* removes the element with smallest priority.
    Break ties however you wish.
    Throws an exception if the heap is empty. */
    void remove ()
    {
      if(items.empty())
      {
        throw std::out_of_range("Error: Heap is empty");
      }
      items[0]=items[(int)items.size()-1];
      items.pop_back();
      heapDown();
    }
    /* returns true iff there are no elements on the heap. */
    bool isEmpty ()
    {
      if(items.empty()) return true;
      return false;
    }
    
    void swap(int indexA,int indexB)
    {
      std::pair<T,int> temp (items[indexA]);
      items[indexA]=items[indexB];
      items[indexB]=temp;
    }
    //as Cote says, bubble up
    void heapUp()
    {
      int index=items.size()-1;
      while(hasParent(index)&& (getPPriority(index)> items[index].second) )
      {
        int pIndex=getPindex(index);
        swap(pIndex, index);
        index=pIndex;
      }
    }
    //as Cote says, trickle down
    void heapDown()
    {
      int index=0;
      while(hasChild(index))
      {
        if(items[index].second<=items[getSmallest(index)].second) break;
        else
        {
          int cIndex=getSmallest(index);
          swap(index,cIndex);
          index=cIndex;
        }
      }
    }

    //returns the parent's index given 
    //the child's index
    int getPindex(int index)
    {
      if(!hasParent(index))
      {
        return -1;
      }
      int pIndex= (index-(index%arry))/arry;
      return pIndex; 
    }
  
    //returns the parent's priority
    int getPPriority(int index)
    {
      if(!hasParent(index))
      {
        return -1;
      }
      return items[getPindex(index)].second;
    }
    //getter function for the smallest child
    int getSmallest(int index)
    {
      if(!hasChild(index))
      {
        return -1;
      }
      int cIndex= index*arry;
      int smallestCP=items[cIndex].second;
      int smallestCI=cIndex;
      for(int k= cIndex+1; k<=cIndex+arry;k++)
      {
        if(k>=(int)items.size()) break;
        if(items[k].second<smallestCP)
        {
          smallestCP=items[k].second;
          smallestCI=k;
        }
      }
      return smallestCI;
    }
    //checks to see if the node at index has a parent
    bool hasParent(int index)
    {
      if(((index-index % arry)/arry>=0) && (index-index % arry)/arry<(int)items.size())
      {
        return true;
      }
      else 
      {
        return false;
      }
    }
    //checks to see if the node at index has a child
    bool hasChild(int index)
    {
      //return getCindex(index)>=0;
      if((index*arry+1)<(int)items.size()) return true;
      return false;
    }

private:
  // whatever you need to naturally store things.
  // You may also add helper functions here.
  int arry;
  //pair will store the object along with 
  std::vector<std::pair<T, int> >items;
};




