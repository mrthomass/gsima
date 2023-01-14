#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// as of sep 30, 2022 we no longer need a seed. This is still in the arguments though.

char *insertSNP(char *ref, int refLen, int SNPSEED);

// this function reads in a reference and makes reads of it and outputs them to a fasta

int main(int argc, char *argv[])
{
	if (argc < 6)
	{	
		printf("Error: reference file argument needed\neg: ./fman SR1.fasta SR1_reads.fasta #READS #SEED #RLength #maxdif\n");
		// sample: ./fman SR1.fasta SR1_reads.fasta #READS #SEED #RLENGTH #MAXDIF
		return(1);
	}

	FILE *fasta = fopen(argv[1], "r"); // read in reference fasta file
	
	if (fasta == NULL)
	{
		printf("Error: invalid file (.fasta)\n");
		return(2);
	}


	// vars
	int RLENGTH;
	int NREAD;
	int SEED;
	int difFac;
	sscanf(argv[3], "%i", &NREAD);
	sscanf(argv[4], "%i", &SEED);
	sscanf(argv[5], "%i", &RLENGTH);
	sscanf(argv[6], "%i", &difFac);
	int randone;
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
	char *ref = malloc(reflen + 1);
	rewind(fasta);
	fscanf(fasta, "%*[^\n]\n%s", ref);
	fclose(fasta);
	char *thisref = insertSNP(ref, reflen, 47); // I am not sure how safe this function is


	// YOU'LL need to remove this thomas
	printf("LOC: %i\n", 47);
	printf("OLD: %s\nNEW: %s\n", ref, thisref);


	// now to writing a reads file

	FILE *fasto = fopen(argv[2], "w");
	srand(time(NULL));
	int pzone;

	for (int i = 0; i < NREAD; i++)
	{
		randone = rand() % (difFac + 1);
		pzone = (reflen - (RLENGTH + randone) + 1);
		randint = rand() % pzone;
		fprintf(fasto, ">%i\n", i + 1); // print to output
		for (int j = 0; j < (RLENGTH + randone); j++)
		{
			fprintf(fasto, "%c", *(thisref + randint + j));
		}
		fprintf(fasto, "\n");
	}

	fclose(fasto);
	free(ref);
	free(thisref);
}


// this function will take a reference sequence and change a nucleotide for the reads, this is analogous to having a different person
char *insertSNP(char *ref, int refLen, int SNPSEED)
{
	srand(time(NULL));
	int pos = rand() % refLen;
	printf("\n\nREMOVE REMOVE REMOVE: %i\n\n", pos); // REMOVE REMOVE REMOVE
	char *thisRef = malloc(refLen + 1);

	for (int i = 0; i < refLen; i++)
	{

		if (i == pos)
		{
			*(thisRef + i) = 'A';
		}
		else
		{
			*(thisRef + i) = *(ref + i);
		}
	}
	return(thisRef);
}


