#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("ERROR: INPUT\n");
		return(1);
	}

	FILE *READS = fopen(argv[1], "r");

	
	int hone;
	int htwo;
	
	
	
	while (!feof(READS))
	{
		fscanf(READS, ">%*i\n");
		hone = ftell(READS);
		fscanf(READS, "%*[^\n]\n");
		htwo = ftell(READS);
		printf("%i\n", htwo - hone - 1); // one more makes it correct
	}

	printf("\n");
	fclose(READS);

}