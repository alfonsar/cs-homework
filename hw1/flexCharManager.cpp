#include "flexCharManager.h"

flexCharManager::flexCharManager(){
 for(int i=0; i<BUF_SIZE;i++)
		{
			buffer[i]='\0';
		}
		used_memory= new Mem_Block*[2];
		free_mem=BUF_SIZE;
		used_mem_size=2;
		for (int i=0;i<BUF_SIZE;i++)
	{
		if(buffer[i]=='\n') //if buffer[i] = null, then
		{
			//new array at i is set to true 
			//true means that there is space 
			availability_array[i]=true;
		}
	}

}


flexCharManager::~flexCharManager(){
	//make sure to free up any allocated memory
    for(int k=0; k<active_requests;k++)
	{
		delete used_memory[k];
	}
	delete [] used_memory;
}
			 
char* flexCharManager::alloc_chars(int n){
	   
	//create a bool array that will store true if the coordinating i
	//index in buffer is null
	
	
	int letters=0;
	
	for (int i=0;i<BUF_SIZE;i++)
	{
		if(availability_array[i])
		{
			//counter for amount of letters
			letters++;
			if(letters==n)
			{
				Mem_Block updated=Mem_Block(n,&buffer[i]);
				active_requests++;
				free_mem=free_mem-n;
				//used_memory[active_requests]= &updated;
				//used_mem_size=used_mem_size-1;
				//if we run out of space, time to resize
				if(active_requests>used_mem_size)//(used_mem_size==0)
				{
					//dynamically allocate more memory by a scale of 2 
					Mem_Block** adjusted= new Mem_Block*[active_requests*2];
					for(int i=0;i<active_requests;i++)
					{
						//copy over elements from old array to resized array
						adjusted[i]=used_memory[i];
					
					}
					// free up used memory
					delete [] used_memory;
					//have used memory point to new resized array
					used_memory=adjusted;
                    used_mem_size=used_mem_size*2;
				}
                for(int k=i;k<n+i;k++)
                {
                    availability_array[k]=false;
                }
                return used_memory[active_requests]->physical_location;
			}
		}
	}

	
	return NULL;
}

void flexCharManager::free_chars(char* p)
{
	//variable to store index
	int place=0;
	//variable to store amount of chars it takes up
	int  space=0;
	//step 1: get index at the beginning of used memory location
		//get amount of space chars take up 
	for (int i=0; i<active_requests;i++)
	{
		if(p==used_memory[i]->physical_location)
		{
			//get the physical location of used memory and store in place variable
			space=used_memory[i]->size;
			//space = address1-address2/size(char)
			place=(used_memory[i]->physical_location-buffer)/sizeof(char);
			delete used_memory[i];
            used_memory[i]=NULL;
            break;
		}
	}
	// step 2: now we reduce mem block 
	if(active_requests==used_mem_size/4)
	{
		//readjust mem block size by dividing by 2
		//if too big, decrease by half 
		Mem_Block** reduced= new Mem_Block*[used_mem_size/2];
		for(int i=0;i<used_mem_size;i++)
		{
			reduced[i]=used_memory[i];
        }
			//used memory now point to reduced array
			used_memory=reduced;
			//divide used_mem by 2 now
			used_mem_size=used_mem_size/2;
			delete [] used_memory;
		}
	
	//Step 3: now time to change the buffer to null characters once chars are freed
	for (int i=place;i<space;i++)
	{
		buffer[i]='\0';
		availability_array[i]=true;
	}
}



