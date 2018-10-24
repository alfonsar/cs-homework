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
    //left string sum
    int l_sum=0;
    ///since lhs and rhs are a constant,
    //if they are uppercase, will use tolower
    std::string left=lhs;
    std::string right=rhs;
    //right string sum
    int r_sum=0;
    int l_len=lhs.length();
    int r_len=rhs.length();
    for(int i=0 ;i<l_len;i++)
    {
        
        //if its a regular number, add it
        if(left[i]>47&&left[i]<58)
        {
          l_sum+=left[i]-'0';
        }
        //if its a letter, add it
        else if((left[i]>='a'&&left[i]<='z')||(left[i]>='A'&&left[i]<='Z'))
        {
          //if its upper case, then lower it
          if(left[i]>='A'||left[i]<='Z')
          {
            left[i]=tolower(left[i]);
          }

          //subtracting 87 to ensure that a's value is 10
          l_sum+=left[i]-87;
        }
              //if symbols or other ascii characters, do nothing 
      //since there value is 0
        else 
        {}
    }
    for(int i=0; i<r_len;i++)
    { 
      
      //if its a regular number, add it
      if(right[i]>47&&right[i]<58) 
      {  
        r_sum+=right[i]-'0';
      }
      //if its a letter, add it
      else if((right[i]>='a'&&right[i]<='z')||(right[i]>='A'&&right[i]<='Z'))
      {
        //if its upper case, lowercase it
        if(right[i]>='A'||right[i]<='Z')
          {
            right[i]=tolower(right[i]);
          }
        //subtracting 87 to ensure that a's value is 10
        r_sum+=right[i]-87;
      }
      //if symbols or other ascii characters, do nothing 
      //since there value is 0
      else 
      {}
    }
    //if the same, then due lex comparison
    if(l_sum==r_sum)
    {
      AlphaStrComp comp1;
      return comp1(lhs,rhs);
    }
    //else return true if right string is greater
    else
    {
      return (l_sum<r_sum);
    }
  }
};