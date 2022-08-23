#include <stdio.h>

// this function maps a read onto a reference, not scalable yet

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("ERROR: read argument required\n");
		return(1);
	}
	
	short const NROW = 2;
	short const NCOL = 10;

	char *read = argv[1];
	char *ref = "ATTGGCGTAA";
	char reads[NROW][NCOL];
	short score[NCOL + 1] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	char doug = 1;
	printf("%c\n", doug + 40);

	for (int i = 0; i < NROW; i++)
	{
		for (int j = 0; j < NCOL; j++)
		{
			if (read[i] == ref[j])
			{
				reads[i][j] = 'A';
				score[j - i]++;
			}
			else
			{
				reads[i][j] = '-';
			}
		}
	}


	int sum = 0;
	int holder = 0;
	for (int i = 0; i < (NCOL + 1); i++)
	{
		if (score[i] > holder)	
		{
			sum = i;
			holder = score[i];
		}
		printf("%i\n", score[i]);
	}

	printf("\nSS: %i\n", sum);

	for (int i = 0; i < NCOL; i++)
	{
		printf("%c\t", ref[i]);
	}

	printf("\n");
	for (int i = 0; i < NCOL; i++)
	{
		if (i >= (sum) && i < (sum + NROW))
		{
			printf("%c\t", read[i - sum]);
		}
		else
		{
			printf("%c\t", '-');
		}
	}
	printf("\n");
}


// if it is equal at multiple places I would like it to print at multiple places