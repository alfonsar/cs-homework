#include <iostream>
#include "functor.h"

using namespace std;

int main() {
  string s1 = "zebra";
  string s2 = "yoyo";
  AlphaStrComp comp1;
  LengthStrComp comp2;
  NumStrComp comp3;

  // Here comp1(s1,s2) is calling comp1.operator() (s1, s2);
  cout << "Blue compared to Red using AlphaStrComp yields " << comp1(s1, s2) << endl;

  // Here comp2(s1,s2) is calling comp2.operator() (s1, s2);
  cout << "Blue compared to Red using LenStrComp yields " << comp2(s1, s2) << endl;
  //Here comp3(s1,s2) is calling comp3.operator() (s1,s2)
  cout<<"Blue compared to Red using NumStrComp yelds "<<comp3(s1,s2)<<endl;
  return 0;
}
