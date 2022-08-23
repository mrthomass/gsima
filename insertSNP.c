#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// this function inserts a snp

int main(void)
{
	char *hodle = "ACCTCG";
	char *hodle2 = malloc(strlen(hodle) + 1);
	
	for (int i = 0; i < strlen(hodle); i++)
	{
		if (i == 2)
		{
			*(hodle2 + i) = 'G';
		}
		else
		{
			*(hodle2 + i) = *(hodle + i);
		}
		printf("%c", *(hodle + i));
	}
	printf("\n");
	printf("%s\n", hodle2);
	
	free(hodle2);
}