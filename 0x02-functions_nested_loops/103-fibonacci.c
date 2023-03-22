#include "main.h"
#include <stdio.h>

/**
 * main - Prints first 50 fibonacci numbers
 * Return: Always Success
 */
int main(void)
{
	long i, n1, n2, temp, sum;

	n1 = 1;
	n2 = 2;
	sum = 0;
	for (i = 0 ; i <= 10000 ; i++)
	{
		if (sum > 4000000)
			break;
		if (n2 % 2 == 0)
			sum += n2;
		temp = n2;
		n2 = n1 + n2;
		n1 = temp;
	}
	printf("%ld\n", sum);
	return (0);
}
