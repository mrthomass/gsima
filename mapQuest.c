#include <stdio.h>
#include <string.h>

int main(void)
{
	// SUM: This is where the read alignment happens

	// Maps the READ to the REF, prints location where it gets the most 'points'
	// Denovo will use this algorithm, but needs to return multiple possible locations


	// having the top 10 or something would be easier,...



	char *const READ = "CGTATTGAGCCT";
	char *const REF = "TTGAGCCTTCGGGAGAACC";
	
	int const scoreThresh = 2;
	

	int const RLEN = strlen(READ);
	int const REFLEN = strlen(REF);

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
				rmap[i][j] = 0;
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
		// finds the top score
		if (score[i] > val)
		{
			val = score[i];
			loci = i;
		}

		// finds the scores over the score threashold
		if (score[i] > scoreThresh)
		{
			printf("%i\n", score[i]); // REMOVE REMOVE REMOVE REMOVE <>
		}
	}

	printf("%i \n", loci - RLEN + 2);
}



