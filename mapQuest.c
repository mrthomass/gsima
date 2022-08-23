#include <stdio.h>
#include <string.h>

int main(void)
{


	char *const READ = "ACGGGGTCTTGGGGG";
	char *const REF = "TTTCTTACGTTTTTTTTTTT";

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
		if (score[i] > val)
		{
			val = score[i];
			loci = i;
		}
	}

	printf("%i \n", loci - RLEN + 2);
}



