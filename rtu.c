#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// our convention is that "ATGC" maps to "0123" 

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("ERROR: check cm args\n");
		return(1);
	}

	int MODE = 0; // "0123" data

	int l = strlen(argv[1]);

	if (*(argv[1]) > 51)
	{
		MODE = 1; // "ATGC" data
	}

	FILE *faster;

	if (MODE == 0)
	{
	// convert to "ATGC" data
		for (int i = 0; i < l; i++)
		{
			
		}
	}
	else
	{
	// convert to "0123" data
	
		for (int i = 0; i < l; i++)
		{
		}
	}
}