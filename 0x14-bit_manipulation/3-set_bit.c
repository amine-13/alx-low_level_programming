#include <stdlib.h>
#include <stdio.h>
#include "main.h"

/**
 * set_bit - Sets the value of a bit to 1 at a given index
 * @n: The number to modify
 * @index: The index in the number to modify
 *
 * Return: 1 if it worked, or -1 if an error occurred
 */
int set_bit(unsigned long int *n, unsigned int index)
{
    // Check if index is valid
    if (index >= sizeof(unsigned long int) * 8)
        return -1;

    // Define a mask to set the bit at the given index
    unsigned long int mask = 1 << index;

    // Set the bit to 1 using bitwise OR and return 1 for success
    *n |= mask;

    return 1;
}
