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
    std::string left=lhs;
    std::string right=rhs;
    int r_sum=0;
    int l_len=lhs.length();
    int r_len=rhs.length();
    for(int i=0 ;i<l_len;i++)
    {
        
        if(left[i]>47||left[i]<58)
        {
          l_sum+=left[i]-'0';
        }
        else if((left[i]>='a'&&left[i]<='z')||(left[i]>='A'&&left[i]<='Z'))
        {
          if(left[i]>='A'||left[i]<='Z')
          {
            left[i]=tolower(left[i]);
          }

          l_sum-=left[i]-87;
        }
        else 
        {

        }
    }
    for(int i=0; i<r_len;i++)
    {
      
      if(right[i]>47||right[i]<58) 
      {  
        r_sum+=right[i]-'0';
      }
      else if((right[i]>='a'&&right[i]<='z')||(right[i]>='A'&&right[i]<='Z'))
      {
        if(right[i]>='A'||right[i]<='Z')
          {
            right[i]=tolower(right[i]);
          }
        r_sum-=right[i]-87;
      }
      else 
      {
      }
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