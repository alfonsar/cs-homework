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
      size=0;
    }
    ~MinHeap () {
      
    }
    /* adds the item to the heap, with the given priority. */
    void add (T item, int priority)
    {
      std::pair<T,int> add(item, priority);
      items.push_back(add);
      size++;
      heapUp();
    }
    /* returns the element with smallest priority.  
    Break ties however you wish.  
    Throws an exception if the heap is empty. */
    const T & peek () const
    {
      if(size==0)
      {
        throw std::out_of_range("Heap is empty");
      }
      return items[0].first;
    }
    /* removes the element with smallest priority.
    Break ties however you wish.
    Throws an exception if the heap is empty. */
    void remove ()
    {
      if(size==0)
      {
        throw std::out_of_range("Heap is empty");
      }
      items[0]=items[size-1];
      items.pop_back();
      size--;
      heapDown();
    }
    /* returns true iff there are no elements on the heap. */
    bool isEmpty ()
    {
      return (size==0);
    }
    
    void swap(int indexA,int indexB)
    {
      std::pair<T,int> temp (items[indexA]);
      items[indexA]=items[indexB];
      items[indexB]=temp;
    }
    void heapUp()
    {
      int index=size-1;
      while(hasParent(index)&& (getPPriority(index)> getCPriority(index)) )
      {
        swap(getPindex(index), index);
        index=getPindex(index);
      }
    }
    void heapDown()
    {
      int index =0;
      while(hasChild(index))
      {
       int smallest=getCindex(index);
       int len=items.size();
       for(int i=1;i<=arry;i++)
       {
         if(smallest+i>len-1) break;
         if(items[smallest+i].second<items[smallest].second)
         {
           smallest=smallest+i;
         }
       } 
       if(items[index]<items[smallest])
       {
         break;
       }
       else
       {
         swap(index,smallest);
       }
       index=smallest;
      }
    }

    //returns the parent's index given 
    //the child's index
    int getPindex(int index)
    {
      int pIndex= (index-index%arry)/arry;
      return pIndex; 
    }
    //returns the child's index given
    //the child's index
    int getCindex(int index)
    {
      int cIndex= index*arry+arry;
      return cIndex;
    }
    //returns the parent's priority
    int getPPriority(int index)
    {
      return items[index-index%arry/arry].second;
    }
    //returns the child's priority
    int getCPriority (int index)
    {
      return items[index*arry+arry].second;
    }
    //checks to see if the node at index has a parent
    bool hasParent(int index)
    {
      return getPindex(index)>=0;
    }
    //checks to see if the node at index has a child
    bool hasChild(int index)
    {
      //return getCindex(index)>=0;
      if((getPindex(index)*arry+1)<(int)items.size()) return true;
      return false;
    }

private:
  // whatever you need to naturally store things.
  // You may also add helper functions here.
  int arry;
  int size;
  std::vector<std::pair<T, int> >items;
};




