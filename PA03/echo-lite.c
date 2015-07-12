#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * * argv)
{
   int ind = 1; 
   int strInd;
   
   for( ; ind < argc; ++ind) 
   {
		for(strInd = 0; strInd < strlen(argv[ind]); strInd++)
		{
			printf("%c", argv[ind][strInd]);
		}
		printf(" ");	
   }
   
   printf("\n");
   return EXIT_SUCCESS;
}