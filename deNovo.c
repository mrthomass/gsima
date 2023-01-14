#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int * mapQuest(char *REF, char *READ, int REFLEN, int RLEN);
char *combineRead(char *readOne, char *readTwo, int loc);


// right now it works well with clean data we can work later for less clean

int main(int argc, char *argv[])
{

	// master ATGCAG

	char *ref = "TG";
	char *read = "AT";
	char *read2 = "GCAG";
	
	int *location = mapQuest(ref, read, strlen(ref), strlen(read));
	
	char *newRef = combineRead(ref, read, location[1]);
	
	// printf("ATGCTACTTGGAGGGCCCATTGAGGTTAAGGGTCCATTCATGATGGATAGAGGAT\n");

	int *location2 = mapQuest(newRef, read2, strlen(newRef), strlen(read2));

	char *extraNewRef = combineRead(newRef, read2, location2[1]);
	
	printf("%s\n", extraNewRef);

	free(newRef);
	free(extraNewRef);

}

int * mapQuest(char *REF, char *READ, int REFLEN, int RLEN)
{

	int rmap[RLEN][REFLEN];
	short score[REFLEN + (RLEN - 1)];

	for (int i = 0; i < RLEN; i++)
	{
		for (int j = 0; j < REFLEN; j++)
		{
			if (READ[i] == REF[j])
			{
				rmap[i][j] = 1;
			}
			else
			{
				rmap[i][j] = -1; // this should be adaptable
			}
		}
	}

	for (int i = 0; i < (REFLEN + (RLEN - 1)); i++)
	{
		score[i] = 0;
	}

	for (int i = 0; i < RLEN; i++)
	{
		for (int j = 0; j < REFLEN; j++)
		{
			score[j + (RLEN - i - 1)] += rmap[i][j];
		}
	}

	int loci = 0;
	int val = score[0];

	for (int i = 1; i < (REFLEN + (RLEN - 1)); i++)
	{
		if (score[i] > val)
		{
			val = score[i];
			loci = i;
		}
	}

	static int opt[2];
	
	opt[0] = val;
	opt[1] = loci - RLEN + 2;

	return(opt); // 0 is powerscore, 1 is position
}



char *combineRead(char *readOne, char *readTwo, int loc)
{

	long a = strlen(readOne);
	long b = strlen(readTwo);
	char *comb;
	

	if (loc > 0)
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

	if (loc <= 0)
	{

	// adding new read to the front
		loc = loc - 1;
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