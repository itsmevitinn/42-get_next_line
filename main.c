#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
	int fd = open ("ola.txt", O_RDONLY);
	int i;

	i = 0; 
	while (i < 4)
	{
		printf("%s", get_next_line(fd));
		i++;
	}
	return (0);
}

