#include <stdlib.h>
#include <stdio.h>
#include "main.h"
/**
 * clear_bit - Sets the value of a bit to 0 at a given index
 * @n: The number to modify
 * @index: The index in the number to modify
 *
 * Return: 1 if it worked, or -1 if an error occurred
 */
int clear_bit(unsigned long int *n, unsigned int index)
{
    // Check if index is valid
    if (index >= sizeof(unsigned long int) * 8)
        return -1;

    // Clear the bit to 0 using bitwise AND and return 1 for success
    *n &= ~(1ul << index);

    return 1;
}
