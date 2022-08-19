#include <stdio.h>
#include <string.h>

// this function maps a read onto a reference sequence

int main(void)
{
	char *ref = "ACTCGGAGTCAGTA"; 	// reference sequence
	char *read = "AGTC";		// read sequence

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
	for (int i = 0; i < bpref; i++)
	{
		if (A[0][i] == 1 && A[1][i+1] == 1 && A[2][i+2] == 1 && A[3][i+3] == 1)
		{
			printf("MY SPOT: %i\n", i+1); // could get Seg Faults here if final is first
		}
	}

	printf("\n\n"); // a print for margin

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

}