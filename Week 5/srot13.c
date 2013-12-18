#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h>


int rot13cmp(void const *a, void const*b)
{
   int i = 0;
   int cmp = 0;
   const char *c = *((const char**) a);
   const char *d = *((const char**) b);
  
   do
   {
	if(c[i] >= 'A' && c[i] <= 'Z' || d[i] >= 'A' && d[i] <= 'Z')
	{
	   cmp = c[i] - d[i];
	}
	if(c[i] >= 'a' && c[i] <= 'z' || d[i] >= 'a' && d[i] <= 'z')
	{
	   cmp = c[i] - d[i]; 
	}
	if(c[i] == '\n' && d[i] != '\n')
	{
	   return -1;
	}
	if(c[i] != '\n' && d[i] == '\n')
	{
	   return 1;				//how is the shorter one considered less?
	}
	if((c[i] == '\n' && d[i] == '\n') && cmp == 0)
	{
	   return cmp; 
	}
	cmp = c[i] - d[i];	
	if( (c[i]>='a' && c[i]<='z') && (d[i]>='a' && d[i]<='z') )
	{
	    if( ((c[i]<='m' && d[i]<='m') || (c[i]>='n' && d[i]>='n')) )
		cmp *= 1;
	    else
		cmp *= -1;
	}
	if( (c[i]>='A' && c[i]<='Z') && (d[i]>='A' && d[i]<='Z') )
	{
	    if( ((c[i]<='M' && d[i]<='M') || (c[i]>='N' && d[i]>='N')) )
	    	cmp *= 1;
	    else
		cmp *= -1;
	}

	i++;
   }while(cmp == 0);

   return cmp; 
}

int main(void)
{
   int bufSize = 2147483647; //Will break at 52 and if i comment out the reallocs it will break at 40 where it will produce 0s
   int memSize = 1000000000; 
   int charCount = 0;
   int wordCount = 0;
   int c;
   char* charArray = (char*) malloc(sizeof(char) * bufSize);
   char** wordArray = (char**) malloc(sizeof(char*) * memSize);
   if(charArray != NULL && wordArray != NULL)
   {
	wordArray[wordCount] = charArray; //Make them point to the same letter spot	
	do
	{
		c = getchar(); //read in each character as an int
		if(c == EOF) //if it is at the end of the file then  
	        {
                  charArray[charCount] = '\n'; //put the new line at the end of the std input
                  wordCount++; //increment the pointer to the next word even if there isn't another one     
                  charCount++; //increment the character count
                  break; //stop the loop and go sort them
                }	

//*********************************************************************************************//
		if(charCount >= bufSize)   //if the character count is = to the bufSize
                {
                        bufSize += 10;
                        charArray = (char*) realloc(charArray, (bufSize) * sizeof(char)); //reallocate the memory
			if(!charArray)
			{
			   fprintf(stderr, "ERROR: realloc failed to reallocate space");
			   exit(1);
			}
                }
//***********************************************************************************************//

		charArray[charCount] = (char)c;
		charCount++;
		
		if(charArray[charCount-1] == '\n') //if you reach the end of the word
		{
		   		   
//********************************************************************************************//
		   if(wordCount >= memSize) //if the word count is the same as the memory
		   {	
			memSize += 10;
			wordArray = (char**) realloc(wordArray, (memSize) * sizeof(char*)); //allocate again
			if(!wordArray)
			{
			   fprintf(stderr, "ERROR: realloc failed to reallocate space");
			   exit(1);
			}
		   }
		   wordCount++;
		   wordArray[wordCount] = (charArray+charCount);
//********************************************************************************************//	  
 
		}	 
	}while(c != EOF); //keep looping until you reach the end of the file
   }
   else
   {
	fprintf(stderr, "Error: Cannot allocate space");
	exit(1);
   }
   qsort(wordArray, wordCount, sizeof(char*), rot13cmp);

   int k;
   for(k = 0; k < wordCount; k++) 
   {
	int i = 0;
	while(i < memSize)
	{
	   char d = wordArray[k][i];
	   int err = putc(d, stdout);

	   if(err == EOF)
	   {
		fprintf(stderr, "ERROR: write error");
		exit(1);
	   }
	
	   if ( d =='\n')
   	   {
		break;
	   }
	   i++;
	}
   }
   return 0;
}
