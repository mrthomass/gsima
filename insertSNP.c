#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// this function causes a snp at location LOCI and it inserts BASE

// just use the char arrays, not the string literals

int main(void)
{
	char *hodle = "ACCTCG"; // this is a string literal, instead use a char local array
	char hodle3[] = "ACCTCG";
	char *hodle2 = malloc(strlen(hodle) + 1);

	int LOCI = 2;
	char BASE = 'T';
	
	for (int i = 0; i < strlen(hodle); i++)
	{
		if (i == LOCI)
		{
			*(hodle2 + i) = BASE;
		}
		else
		{
			*(hodle2 + i) = *(hodle + i);
		}
		printf("%c", *(hodle + i));
	}
	printf("\n");
	printf("%s\n", hodle2);
	
	
	for (int h = 0; h < strlen(hodle); h++)
	{
		printf("%c\n", *(hodle + h));
		printf("%p\n", hodle + h);
	}

	hodle3[2] = 'G';
	printf("%s\n", hodle3);
	free(hodle2);
}