#include <stdio.h>

int main(void)
{
	int const RLEN = 5;
	int const REFLEN = 100;

	char *const READ = "ACGAA";
	char *const REF = "CTAGTATCACGAGCAGCTGGGGGCCAGGCAGGTATTGACGAACCTCCCATTGAGTAGTCTCAACTCGCCCACTGACTTTTTGTGTGAGCGAGTATTCACC";

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

	for (int i = 0; i < (REFLEN + (RLEN - 1)); i++)
	{
		printf("%i|", score[i]);
	}
	printf("\n");
}



