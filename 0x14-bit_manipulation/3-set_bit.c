#include <stdlib.h>
#include <stdio.h>
#include "main.h"
/**
 * set_bit - sets the value of a bit to 1 at a given index
 * @n: a pointer to the number to modify
 * @index: the index of the bit to set
 *
 * Return: 1 if it worked, or -1 if an error occurred
 */
int set_bit(unsigned long int *n, unsigned int index)
{
    // Check if index is valid
    if (index >= sizeof(unsigned long int) * 8)
        return (-1);

    // Define a mask for the bit to be modified
    unsigned long int mask = 1 << index;

    // Use the mask to modify the bit and return 1 to indicate success
    *n |= mask;
    return (1);
}
