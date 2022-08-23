#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// prototype
int seqLen(FILE *fasta);



// this function maps a read onto a reference sequence exactly

int main(int argc, char *argv[])
{
	// first I will read in the reference seq

	if (argc < 2)
	{
		printf("ERROR: incorrect command arguments\n");
		return(1);
	}
	
	FILE *fasta = fopen(argv[1], "r");
	if (fasta == NULL)
	{
		printf("ERROR: file does not exist\n");
		return(2);
	}
	int refLen = seqLen(fasta);
	char *ref = malloc(refLen + 1);
	fscanf(fasta, "%*[^\n]\n");
	fscanf(fasta, "%s", ref);
	fclose(fasta);



	char *read = "TAG";		// read sequence

	int bpref = strlen(ref);
	int bpread = strlen(read);

	int A[bpread][bpref]; // mat[row][col]
	

	// this mechanism fills in the matrix with matches
	for (int i = 0; i < bpread; i++)
	{
		for (int j = 0; j < bpref; j++)
		{
			if (ref[j] == read[i])
			{
				A[i][j] = 1;
			}
			else
			A[i][j] = 0;
		}
	}


// this should probably be in a separate function called like checkRead
// this is hard coded for bpread == 4
//	for (int i = 0; i < bpref; i++)
//	{
//		if (A[0][i] == 1 && A[1][i+1] == 1 && A[2][i+2] == 1 && A[3][i+3] == 1)
//		{
//			printf("MY SPOT: %i\n", i+1); // could get Seg Faults here if final is first
//		}
//	}

//	printf("\n\n"); // a print for margin

// this is what decides what a match is

	for (int i = 0; i < bpref; i++)
	{
		if (A[0][i] == 1)
		{
			int buff = 1;
			for (int j = 1; j < bpread; j++)
			{
				if (A[j][i+j] == 1)
				{
					buff++;
				}
			}

			if (buff > bpread - 2)
			{
				if (buff == bpread)
				{
					printf("MY SPOT (2): %i\n", i + 1);
				}
				else 
				{
					printf("MY ALMOST: %i\n", i + 1);
				}
			}

		}
	}



	for (int i = 0; i < bpread; i++)
	{
		for (int j = 0; j < bpref; j++)
		{
			printf("%i\t", A[i][j]);
		}
		printf("\n");
	}

	free(ref); // FREEING THE REFERENCE
}


// helper function to get length of the reference

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

