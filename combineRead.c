#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char *combineRead(char *readOne, char *readTwo, int loc);

int main(void)
{
	char *one = "TGGAA";
	char *two = "ATGTCTGG";
	char *master = combineRead(one, two, -5);

	printf("%s\n", master);
	free(master);
}

char *combineRead(char *readOne, char *readTwo, int loc)
{
	int readFirst = 1;

	if (loc < 0)
	{
	// this means the readTwo is first, so the system is slightly switched
		readFirst = -1;
	}

	long a = strlen(readOne);
	long b = strlen(readTwo);
	char *comb;
	

	if (readFirst > 0)
	{
	// adding new read to the end

		comb = malloc(b + loc);
		for (int i = 0; i < (b + loc); i++)
		{
			if (i < loc - 1) // these are important, who do you want to use for the transition pieces (same below)
			{
				*(comb + i) = *(readOne + i);
			}
			else
			{
				*(comb + i) = *(readTwo + i - loc + 1);
			}
		
		}
	}

	if (readFirst < 0)
	{
	// adding new read to the front
	
		comb = malloc(a - loc);
		for (int i = 0; i < (a - loc); i++)
		{
			if (i < 1 - loc)
			{
				*(comb + i) = *(readTwo + i);
			}
			else
			{
				*(comb + i) = *(readOne + i + loc);
			}
		}
	}

	
	return(comb);
}