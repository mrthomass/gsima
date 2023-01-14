#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int * mapQuest(char *REF, char *READ, int REFLEN, int RLEN);
char *combineRead(char *readOne, char *readTwo, int loc);
int *sumFast(FILE *fasta);


// right now it works well with clean data we can work later for less clean

int main(int argc, char *argv[])
{
	FILE *readFile = fopen("SR1_reads.fasta", "r");
	if (readFile == NULL)
	{
		printf("Error: READ FILE\n");
		return(1);
	}

	int *charles = sumFast(readFile);

	printf("NUM READS: %i\n", charles[0]);
	
	for (int i = 1; i < charles[0] + 1; i++)
	{
		printf("R#: %i\t%i\n", i, charles[i]);
	}
	
	fclose(readFile);
	free(charles);

}

// this function maps the read onto the ref to the best of its abbility and returns the likely position and confidence
int * mapQuest(char *REF, char *READ, int REFLEN, int RLEN)
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
				rmap[i][j] = -1; // this should be adaptable
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

	static int opt[2];
	
	opt[0] = val;
	opt[1] = loci - RLEN + 2;

	return(opt); // 0 is powerscore, 1 is position
}



char *combineRead(char *readOne, char *readTwo, int loc)
{

	long a = strlen(readOne);
	long b = strlen(readTwo);
	char *comb;
	

	if (loc > 0)
	{
	// adding new read to the end

		comb = malloc(b + loc);
		for (int i = 0; i < (b + loc); i++)
		{
			if (i < loc - 1) // these are important, who do you want to use for the transition pieces (same below)
			{
				*(comb + i) = *(readOne + i);
			}
			else
			{
				*(comb + i) = *(readTwo + i - loc + 1);
			}
		
		}
	}

	if (loc <= 0)
	{

	// adding new read to the front
		loc = loc - 1;
		comb = malloc(a - loc);
		for (int i = 0; i < (a - loc); i++)
		{
			if (i < 1 - loc)
			{
				*(comb + i) = *(readTwo + i);
			}
			else
			{
				*(comb + i) = *(readOne + i + loc);
			}
		}
	}

	
	return(comb);
}


// this function summarizes the fasta file of reads and outputs an array, at [0] it's the number of reads in the file
int *sumFast(FILE *fasta)
{
	char chVal;
	int nRead = 0;

	// step One get the number of reads based on '>'s' (62's)

	while ((chVal = fgetc(fasta)) != EOF)
	{
		if (chVal == 62)
		{
			nRead++;
		}
	}

	rewind(fasta);

	// step Two get the length of each of the nRead's

	int *oparray = malloc(sizeof(int) * (nRead + 1));

	oparray[0] = nRead;

	fscanf(fasta, "%*[^\n]\n");

	int a = ftell(fasta);
	int b;

	for (int i = 1; i < nRead + 1; i++)
	{
		fscanf(fasta, "%*[^\n]\n");
		b = ftell(fasta);
		if (i != nRead)
		{
			fscanf(fasta, "%*[^\n]\n");
		}
		oparray[i] = b - a - 1; // this is the cutting >>
		a = ftell(fasta);
	}

	oparray[nRead]++; // add one len to the final due to cuting

	return(oparray);
}



