#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

int main(int argc, char * * argv)
{
	int invert = FALSE;
    int line = FALSE;
    int quiet = FALSE;
	
    int ind = 1;
   
    for( ; ind < argc; ++ind) 
    {
		if(strcmp(argv[ind], "--help") == 0) 
		{
			printf("Usage: grep-lite [OPTION]... PATTERN\n"
					"Search for PATTERN in standard input. PATTERN is a\n"
					"string. grep-lite will search standard input line by\n"
					"line, and (by default) print out those lines which\n"
					"contain pattern as a substring.\n"
					"\n"
					"  -v, --invert-match     print non-matching lines\n"
					"  -n, --line-number      print line numbers with output\n"
					"  -q, --quiet            suppress all output\n"
					"\n"
					"Exit status is 0 if any line is selected, 1 otherwise;\n"
					"if any error occurs, then the exit status is 2.\n");
			return EXIT_SUCCESS;
		}
    
		else if((strcmp(argv[ind], "-v") == 0) || (strcmp(argv[ind], "--invert-match") == 0)) 
			invert = TRUE;
		else if((strcmp(argv[ind], "-n") == 0) || (strcmp(argv[ind], "--line-number") == 0)) 
			line = TRUE;
		else if((strcmp(argv[ind], "-q") == 0) || (strcmp(argv[ind], "--quiet") == 0)) 
			quiet = TRUE;
    }
	
	if(quiet)
	{
		return EXIT_SUCCESS;
	}
  
	
	if(invert)
	{
		char str[2000];
		int i = 1;
		while (fgets(str, 2000, stdin) != NULL)
		{
			if(strstr(str, argv[ind - 1]) == NULL)
			{
				if(line)
					printf("%d:%s", i, str);
				else
					printf("%s", str);
			}
			
			i++;
		}
	}
   
    if(line)
	{
		char str[2000];
		int i = 1;
		while (fgets(str, 2000, stdin) != NULL)
		{
			if(strstr(str, argv[ind - 1]) != NULL)
				printf("%d:%s", i, str);
				
			i++;
		}
    }
	
	if(!line && !quiet && !invert)
	{
		char str[2000];
		
		while (fgets(str, 2000, stdin) != NULL)
		{
			if(strstr(str, argv[ind - 1]) != NULL)
				printf("%s", str);
		}
	}
	
	
   return EXIT_SUCCESS;
}