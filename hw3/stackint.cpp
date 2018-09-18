 #include "stackint.h"
 StackInt::StackInt(){

 }
  StackInt::~StackInt(){

  }

  /**
   * Returns true if the stack is empty, false otherwise
   */
  bool StackInt:: empty() const;

  /**
   * Pushes a new value, val, onto the top of the stack
   */
  void StackInt:: push(const int& val);

  /**
   * Returns the top value on the stack
   */
  int StackInt::  top() const;

  /**
   * Removes the top element on the stack
   */
  void StackInt::pop();