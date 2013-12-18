#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

//pread does not advance in the file, pointer
//read advances the pointer in the file

//the first argument might need an open function

int main()
{
   char charBuff[1];
   while(read(0, charBuff, 1) > 0)
   {
      write(1, charBuff, 1);
   }
   return 0;
}
