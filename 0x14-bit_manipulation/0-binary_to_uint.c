#include <stdlib.h>
#include <stdio.h>
#include "main.h"

/**
  * binary_to_uint - Converts a binary number to an unsigned int
  * @binary: The binary string to convert
  *
  * Return: The positive number converted from a binary
  */
unsigned int binary_to_uint(const char *binary)
{
	unsigned int length = 0, bit_count = 0, decimal = 0;

	if (binary == NULL)
		return (0);

	length = string_length(binary);
	for (int i = length - 1; i >= 0; i--)
	{
		if (binary[i] != '0' && binary[i] != '1')
			return (0);

		if (binary[i] == '1')
			decimal += 1 << bit_count;

		bit_count++;
	}

	return (decimal);
}

/**
  * string_length - Returns the length of a string
  * @str: String to count
  *
  * Return: String length
  */
int string_length(const char *str)
{
	int length = 0;

	for (; str[length] != '\0'; length++)
		continue;

	return (length);
}
