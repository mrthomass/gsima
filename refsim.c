#include <stdio.h>
#include <stdlib.h>

// This function simulates a reference sequence

int main(int argc, char *argv[]) // void
{
	if (argc != 4)
	{
		// input is:: call seqLen randSeed opFile
		printf("ERROR: check inputs\neg. ./refsim 10 4 ~/Genomics/GSIM/SR1.fasta\n");
		return(1);
	}
	
	FILE *fasta;

	fasta = fopen(argv[3], "w");
	fprintf(fasta, ">SR_002394.1 Thomsonitis A, complete genome\n");
	
	int ri;
	int SEED;
	int GLEN;
	sscanf(argv[1], "%i", &GLEN); 
	sscanf(argv[2], "%i", &SEED);
//	char *seq = malloc(GLEN + 1);
	char *nuc = "ATGC";
	srand(SEED);

	
	for (int i = 0; i < GLEN; i++)
	{
		ri = rand() % 4;
		fprintf(fasta, "%c", *(nuc + ri));
//		seq[i] = *(nuc + ri);
	}


//	free(seq);
	fclose(fasta);
}
