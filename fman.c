#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if (argc < 2)
	{	
		printf("Error: file argument needed\n");
		return(1);
	}

	FILE *fasta = fopen(argv[1], "r"); // read in reference fasta file
	
	if (fasta == NULL)
	{
		printf("Error: invalid file (.fasta)\n");
		return(2);
	}


	// vars
	int const RLENGTH = 5;
	int const NREAD = 10;
	int const SEED = 8;
	int randint;
	char reads[NREAD][RLENGTH];
	// vars


	// this is how you find the size of the reference in bp given that all are char's

	int reflen = 0; // this should probably be a long**
	fscanf(fasta, "%*[^\n]\n"); // skips header
	reflen -= ftell(fasta);
	fseek(fasta, 0, SEEK_END);
	reflen += ftell(fasta);

	// now to extract the ref
	char *ref = malloc(reflen);
	rewind(fasta);
	fscanf(fasta, "%*[^\n]\n");
	fscanf(fasta, "%s", ref);
	fclose(fasta);


	srand(SEED);
	int pzone = (reflen - RLENGTH + 1);

	for (int i = 0; i < NREAD; i++)
	{
		randint = rand() % pzone;
		for (int j = 0; j < RLENGTH; j++)
		{
			reads[i][j] = *(ref + randint + j);
		}
	}


	// remove this later this is for printing the reads

	printf("REFERENCE:\t%s\n", ref);
	
	for (int i = 0; i < NREAD; i++)
	{
		randint = rand() % pzone;
		printf("READ (%i):\t", i + 1);
		for (int j = 0; j < RLENGTH; j++)
		{
			printf("%c", reads[i][j]);
		}
		printf("\n");
	}

	// remove
	
	free(ref);
}