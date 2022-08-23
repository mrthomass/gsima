#include <stdio.h>
#include <stdlib.h>

// this function reads in a reference and makes reads of it and outputs them to a file

int main(int argc, char *argv[])
{
	if (argc < 3)
	{	
		printf("Error: reference file argument needed\n");
		return(1);
	}

	FILE *fasta = fopen(argv[1], "r"); // read in reference fasta file
	
	if (fasta == NULL)
	{
		printf("Error: invalid file (.fasta)\n");
		return(2);
	}


	// vars
	int const RLENGTH = 15;
	int const NREAD = 1;
	int const SEED = 87;
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

	// now to writing a reads file

	FILE *fasto = fopen(argv[2], "w");

	srand(SEED);
	int pzone = (reflen - RLENGTH + 1);

	for (int i = 0; i < NREAD; i++)
	{
		randint = rand() % pzone;
		fprintf(fasto, ">%i\n", i + 1); // print to output
		for (int j = 0; j < RLENGTH; j++)
		{
			fprintf(fasto, "%c", *(ref + randint + j));
		}
		fprintf(fasto, "\n");
	}

	fclose(fasto);
	free(ref);
}