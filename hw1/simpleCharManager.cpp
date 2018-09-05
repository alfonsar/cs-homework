#include <cstddef>
#include "simpleCharManager.h"



simpleCharManager::simpleCharManager(){
	
	for(int i=0; i<BUF_SIZE;i++)
        {
        	buffer[i]='\0';
        }
  first_element=false;
  last_element=false;
}

simpleCharManager::~simpleCharManager(){}

char* simpleCharManager::alloc_chars(int n)
{

   for(int i=0; i<BUF_SIZE;i++)
   {
        if(buffer[i]=='\0')
        {
            for(int j=i;j<i+n;j++)
            {
                first_element=true;
                free_place=&buffer[j];
                if(buffer[j]!='\0')
                {
                   first_element=false;
                   break;     
                }
            } 
            last_element=true;
            if(first_element&&last_element)   
            {
                first_element=false;
                last_element=false;
                return free_place;
            }
        }
   }
   return NULL;
}
             

void simpleCharManager::free_chars(char* p)
{
   int place=0;
   for(int i=0; i<BUF_SIZE;i++)
   {
        if(buffer[i]==*p)
        {
            place=i;
            break;    
        }
   }

   for(int i=place;i<BUF_SIZE;i++)
   {
        buffer[i]='\0';
   }

       


}         




