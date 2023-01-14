#include <stdio.h>

int seqLen(FILE *fasta);

int main(void)
{
	FILE *READf = fopen("SR1_reads.fasta", "r");
	if (READf == NULL)
	{
		printf("Error: READ FILE\n");
		return(1);
	}
	
	printf("ALLEGED LENGTH: %i\n", seqLen(READf));

}

int seqLen(FILE *fasta)
{
	int reflen = 0;
	fscanf(fasta, "%*[^\n]\n"); 
	printf("cursor: %li\n", ftell(fasta));
	reflen -= ftell(fasta);
	fseek(fasta, 0, SEEK_CUR);
	reflen += ftell(fasta);
	rewind(fasta);
	return(reflen);
}