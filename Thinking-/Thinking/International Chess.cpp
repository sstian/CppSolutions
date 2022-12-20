#include <stdio.h> 
#include <stdlib.h>
#include <math.h> 
void main()
{
	int i, j;
	system("cmd /c chcp 437");
	for (i = 0; i<8; i++)
	{
		for (j = 0; j<8; j++)
			if ((i + j) % 2 == 0)
				printf("%c", 219);
			else
				printf(" ");
		printf("\n");
	}
}