#include <string>

struct AlphaStrComp {
  bool operator() (const std::string& lhs, const std::string& rhs)
  { // Uses string's built in operator<
    // to do lexicographic (alphabetical) comparison
    return (lhs < rhs);
  }
};

struct LengthStrComp {
  bool operator()(const std::string& lhs, const std::string& rhs)
  { // Compares strings by size;
    // Breaks ties by lexicographic comparison
    return (   (lhs.size() < rhs.size())
            || (lhs.size() == rhs.size() && lhs < rhs));
  }
};

struct NumStrComp{
  bool operator()(const std:: string&lhs, const std::string& rhs)
  {
    int l_sum=0;
    int r_sum=0;
    int l_len=lhs.length();
    int r_len=rhs.length();
    for(int i=0 ;i<l_len;i++)
    {
        if(lhs[i]<10) {l_sum+=lhs[i]-'0';}
        else{l_sum+=lhs[i]-'0'-39;}
    }
    for(int i=0; i<r_len;i++)
    {
      if(rhs[i]<10) {r_sum+=rhs[i]-'0';}
      else{r_sum+=rhs[i]-'0'-39;}
    }
    if(l_sum==r_sum)
    {
      AlphaStrComp comp1;
      return comp1(lhs,rhs);
    }
    else
    {
      return (l_sum<r_sum);
    }
  }
};