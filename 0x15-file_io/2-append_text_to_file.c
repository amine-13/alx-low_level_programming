#include <stdio.h>
#include "main.h"

/**
 * append_text_to_file - appends text to the end of a file
 * @filename: the name of the file to append to
 * @text_content: the text to append
 *
 * Return: 1 on success, -1 on failure
 */
int append_text_to_file(const char *filename, char *text_content)
{
	int fd, num_written;

	if (!filename)
	{
		fprintf(stderr, "Error: filename is null\n");
		return (-1);
	}

	fd = open(filename, O_WRONLY | O_APPEND);
	if (fd == -1)
	{
		fprintf(stderr, "Error: could not open file %s\n", filename);
		return (-1);
	}

	if (text_content)
	{
		num_written = write(fd, text_content, _strlen(text_content));
		if (num_written == -1 || num_written != _strlen(text_content))
		{
			fprintf(stderr, "Error: could not write to file %s\n", filename);
			close(fd);
			return (-1);
		}
	}

	close(fd);
	return (1);
}

/**
 * _strlen - Returns the length of a string
 * @s: String to count
 *
 * Return: String length
 */
int _strlen(char *s)
{
	int c = 0;

	while (s[c])
		c++;

	return (c);
}
