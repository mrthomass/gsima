#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int seqLen(FILE *fasta);
int mapQuest(char *REF, char *READ, int REFLEN, int RLEN);
void subgrapher(char *READ, int RLEN, int pos, int REFLEN);

// this function reads in a reference and a file of reads and maps them and writes to a sam file

int main(int argc, char *argv[])
{
	if (argc < 3)
	{
		printf("ERROR: File arguments required\n");
		return(1);
	}
	
// READING IN THE REFERENCE FILE
	FILE *REFf = fopen(argv[1], "r");
	if (REFf == NULL)
	{
		printf("ERROR: Reference file\n");
		return(2);
	}
	int refLen = seqLen(REFf);
	char *REFr = malloc(refLen + 1);
	fscanf(REFf, "%*[^\n]\n%s", REFr);
	fclose(REFf);

// READING IN THE READS FILE
	FILE *READf = fopen(argv[2], "r");
	if (READf == NULL)
	{
		printf("ERROR: Read file\n");
		return(3);
	}

	int RID;
	char *READr = malloc(15 + 1); // this is not scalable

//	while (!feof(READf)) // this will be for when we go scalable
//	{
//		fscanf(READf, ">%i\n", &RID);
//		fscanf(READf, "%s", READr);
//	}



// THIS WILL ALL NEED TO BE MADE INTO LOOP ----------------------------------------------------------
	
	printf("%s\n", REFr);
	int readLen;
	int refPos;

	while (!feof(READf))
	{
		fscanf(READf, ">%i\n", &RID);
		fscanf(READf, "%s\n", READr);
		readLen = strlen(READr);
		refPos = mapQuest(REFr, READr, refLen, readLen);
		subgrapher(READr, readLen, refPos, refLen);
	}


// THIS WILL ALL NEED TO BE MADE INTO LOOP ----------------------------------------------------------

	printf("\n");

	fclose(READf);
	free(REFr);
	free(READr);
}


// this function gets the length of a fasta sequence
int seqLen(FILE *fasta)
{
	int reflen = 0;
	fscanf(fasta, "%*[^\n]\n"); 
	reflen -= ftell(fasta);
	fseek(fasta, 0, SEEK_END);
	reflen += ftell(fasta);
	rewind(fasta);
	return(reflen);
}


int mapQuest(char *REF, char *READ, int REFLEN, int RLEN)
{

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

	return(loci - RLEN + 2);
}

void subgrapher(char *READ, int RLEN, int pos, int REFLEN)
{
	int sup = REFLEN - pos - RLEN;
	for (int i = 0; i < (pos - 1); i++)
	{
		printf("-");
	}

	for (int i = 0; i < RLEN; i++)
	{
		printf("%c", READ[i]);
	}
	for (int i = 0; i < (sup + 1); i++)
	{
		printf("-");
	}
	printf("\n");
}
