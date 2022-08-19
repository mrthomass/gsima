#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int const refbp = 5;
	int const readbp = 3;
	int ref[refbp] = {0, 1, 0, 2, 1};
	int read[readbp] = {1, 0, 2};

	int nreg = refbp - readbp + 1;
	
	double varx[nreg];
	double meanx[nreg];
	double cov[nreg];
	double r[nreg];

	double meany = (read[0] + read[1] + read[2]) / readbp;
	double vary = (read[0] - meany) * (read[0] - meany) + (read[1] - meany) * (read[1] - meany) + (read[2] - meany) * (read[2] - meany);

	for (int i = 0; i < nreg; i++)
	{
		meanx[i] = (ref[i] + ref[i + 1] + ref[i + 2]) / readbp;
		varx[i] = (ref[i] - meanx[i]) * (ref[i] - meanx[i]) + (ref[i + 1] - meanx[i]) * (ref[i + 1] - meanx[i]) + (ref[i + 2] - meanx[i]) * (ref[i + 2] - meanx[i]);
		cov[i] = (ref[i] - meanx[i]) * (read[0] - meany) + (ref[i+1] - meanx[i]) * (read[1] - meany) + (ref[i+2] - meanx[i]) * (read[2] - meany);
		r[i] = (cov[i] * cov[i]) / (vary * varx[i]);
	}


	int pos = 0;

	for (int i = 1; i < nreg; i++)
	{
		if (r[i] > r[pos])
		{
			pos = r[i];
		}
	}

	
	FILE *sam;
	sam = fopen("/Users/thomas/Genomics/GSIM/SR_002394.sam", "w");

	fprintf(sam, "[%i, %i, %i]\n", pos, pos + 1, pos + 2);
	fprintf(sam, "%i%i%i\n", read[0], read[1], read[2]);

	fclose(sam);
	return(0);
}