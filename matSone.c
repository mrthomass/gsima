#include <stdio.h>
#include <stdlib.h>

// this fuction will load in a reference and a read in fasta format and output the reads plus the
// length of the units

int readLen(FILE *fasta);
int mapQuest(char *REF, char *READ);

int main(int argc, char *argv[])
{
	if (argc < 3)
	{
		printf("ERROR: invalid file argument\n");
		return(1);
	}
	
	FILE *ofasta = fopen(argv[1], "r");
	FILE *sfasta = fopen(argv[2], "r");

	if (ofasta == NULL || sfasta == NULL)
	{
		printf("ERROR: invalid file\n");
		return(2);
	}

	int reflin = readLen(ofasta);
	int readlin = readLen(sfasta);

	char *ref = malloc(reflin + 1);
	char *read = malloc(readlin + 1);
	fscanf(ofasta, "%*[^\n]\n%s", ref);
	fscanf(sfasta, "%*[^\n]\n%s", read);

	mapQuest(ref, read);


	free(ref);
	free(read);
	fclose(ofasta);
	fclose(sfasta);
}

// this function will return the ref len of a fasta file

int readLen(FILE *fasta)
{
	int reflen = 0;
	fscanf(fasta, "%*[^\n]\n");
	reflen -= ftell(fasta);
	fseek(fasta, 0, SEEK_END);
	reflen += ftell(fasta);
	rewind(fasta);
	return(reflen);
}


// this function will map the read onto the reference, not scalable yet


int mapQuest(char *ref, char *read)
{
	// only works with the following constraints now
	short const NROW = 2;
	short const NCOL = 10;

	char reads[NROW][NCOL];
	short score[NCOL + 1] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


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
	return(0);
}
