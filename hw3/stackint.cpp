 #include "stackint.h"
 StackInt::StackInt()
 {

 }
  StackInt::~StackInt(){

  }

  /**
   * Returns true if the stack is empty, false otherwise
   */
  bool StackInt:: empty() const
  {
    if(list.size()==0)
    {
      return true;
    }
    return false;
  }

  /**
   * Pushes a new value, val, onto the top of the stack
   */
  void StackInt:: push(const int& val)
  {
   
   list.push_back(val);
   return;
  }
  /**
   * Returns the top value on the stack
   */
  int StackInt::  top() const
  {
    int last=list.size()-1;
    return list.get(last);
  }
  /**
   * Removes the top element on the stack
   */
  void StackInt::pop()
  {
    int last=list.size()-1;
    list.remove(last);
  }
  int StackInt::size()
  {
    return (int)list.size();
  }