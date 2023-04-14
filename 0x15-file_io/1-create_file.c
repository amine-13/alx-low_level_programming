#include "main.h"
#include <fcntl.h>
#include <unistd.h>

/**
 * create_file - creates a file with given content
 * @filename: the name of the file to create
 * @text_content: the content to put in the file
 *
 * Return: 1 on success, -1 on failure
 */
int create_file(const char *filename, char *text_content)
{
	int fd, num_written;

	if (filename == NULL)
		return (-1);

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
		return (-1);

	if (text_content != NULL && *text_content != '\0')
	{
		num_written = write(fd, text_content, strlen(text_content));
		if (num_written == -1 || num_written != strlen(text_content))
		{
			close(fd);
			return (-1);
		}
	}

	close(fd);
	return (1);
}
