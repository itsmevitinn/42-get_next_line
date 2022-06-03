#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
	int fd = open("ola.txt", O_RDONLY);
	int fd2 = open("salve.txt", O_RDONLY);
	int fd5 = open("kaka.txt", O_RDONLY);
	int fd3 = open("wigol.txt", O_RDONLY);
	int fd4 = open("rato.txt", O_RDONLY);
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		printf("%s", line);
		line = get_next_line(fd2);
		printf("%s", line);
		line = get_next_line(fd5);
		printf("%s", line);
		line = get_next_line(fd4);
		printf("%s", line);
		line = get_next_line(fd3);
		printf("%s", line);
		if (!line)
			break;
		free(line);
	}
	return (0);
}

