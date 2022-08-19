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

	// this is how you find the size of the reference in bp given that all are char's

	int reflen = 0; // this should probably be type long

	// this complex finds the reference length in bp
	fscanf(fasta, "%*[^\n]\n"); // skips header
	reflen -= ftell(fasta);
	fseek(fasta, 0, SEEK_END);
	reflen += ftell(fasta);
	printf("%i\n", reflen);

	// now to extract the ref
	char *ref = malloc(reflen);
	rewind(fasta);
	fscanf(fasta, "%*[^\n]\n%s", ref);
	
	printf("%s\n", ref);
	
	free(ref);
	fclose(fasta);
}