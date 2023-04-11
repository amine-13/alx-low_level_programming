#include <stdlib.h>
#include <stdio.h>
#include "main.h"
#include "main.h"

/**
 * get_bit - Returns the value of a bit at a given index
 * @n: The number to get the bit from
 * @index: The index of the bit to get
 *
 * Return: The value of the bit at index index or -1 if an error occurred
 */
int get_bit(unsigned long int n, unsigned int index)
{
	unsigned long int mask = 1UL << index;

	if (index > sizeof(unsigned long int) * 8 - 1)
		return (-1);

	return ((n & mask) ? 1 : 0);
}
