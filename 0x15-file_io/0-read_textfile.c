#include "main.h"

/**
  * read_textfile - ...
  * @filename: The source file
  * @letters: Number of letters to reads and prints
  *
  * Return: ...
  */
ssize_t read_textfile(const char *filename, size_t letters)
{
	int fd;
	ssize_t readed;
	char buff[1024];

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (0);

	while ((readed = read(fd, buff, sizeof(buff))) > 0 && letters > 0)
	{
		if (letters < readed)
			readed = letters;

		if (write(STDOUT_FILENO, buff, readed) != readed)
		{
			close(fd);
			return (0);
		}

		letters -= readed;
	}

	close(fd);
	return (letters == 0 ? readed : 0);
}
