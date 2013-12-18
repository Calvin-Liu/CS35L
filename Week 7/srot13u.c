#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> 
#include <stdbool.h>
#include <sys/stat.h>

int rotCount = 0;

int rot13cmp(void const *a, void const*b)
{
   rotCount++;
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
   int bufSize = 1; 
   int charCount = 0;
   int wordCount = 0;
   int b = 0;
   int puttingWordsIn = 0;
   int charPointer = 0;
   int didSizeChange;
   bool STDInput = false;
   char* charArray;
   
   struct stat fileStats;
   fstat(0, &fileStats);
   if(S_ISREG(fileStats.st_mode))
   {
       charArray = (char*) malloc(fileStats.st_size);
   }
   else
   {
       charArray = (char*) malloc(sizeof(char) * bufSize);
       STDInput = true;
   }

   int fileSize = fileStats.st_size;
   while(read(0, (charArray+charCount), 1) > 0)
   {
	if( (fileStats.st_size == 0) && !STDInput)
        {
           fileSize++;
	   charArray = (char*)realloc(charArray, fileSize);
        }

	if( (charCount >= bufSize) )  
        {
             bufSize += 10;
             charArray = (char*) realloc(charArray, (bufSize) * sizeof(char)); 
        }
	
        charCount++;
   }

   if(charArray[charCount] != '\n') 
   {
      charArray[charCount] = '\n';
      charCount++;
   }
   
   while(charPointer < charCount)
   {
      if(charArray[charPointer] == '\n')
      {
      	  wordCount++;
      }
      charPointer++;
   }

   char** wordArray = (char**) malloc(sizeof(char*) * wordCount);
   wordArray[b] = charArray;
	
   while(puttingWordsIn < charCount)
   {
       if(charArray[puttingWordsIn] == '\n')
       {
	   b++;
    	   wordArray[b] = (charArray+puttingWordsIn+1);
       }
       puttingWordsIn++;
   }

   qsort(wordArray, wordCount, sizeof(char*), rot13cmp);

   int k;
   for(k = 0; k < wordCount; k++) 
   {
	int i = 0;
	while(i < charCount)
	{
	   char d = wordArray[k][i];
	   write(1, &d, 1);
           if ( d =='\n')
   	   {
		break;
	   }
	   i++;
	}
   }
   fprintf(stderr, "Number of comparisons: %d \n", rotCount);
   
   int f;
//   free(charArray);
//   for(f = 0; f < wordCount; f++)
//   {
//      free(wordArray);
//   }
   return 0;
}
