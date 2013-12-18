#include <stdio.h> 

int main()
{
   int asciiVal;
   char asciiLetter;
   do
   {
      asciiVal = getchar();
      asciiLetter = (char)asciiVal;
      putchar(asciiLetter); 
   }while(asciiVal != EOF);
}
