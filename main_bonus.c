/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 13:01:51 by vsergio           #+#    #+#             */
/*   Updated: 2022/06/05 13:01:54 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
	int fd1 = open("teste1.txt", O_RDONLY);
	int fd2 = open("teste2.txt", O_RDONLY);
	int fd3 = open("teste3.txt", O_RDONLY);
	int fd4 = open("teste4.txt", O_RDONLY);
	int fd5 = open("teste5.txt", O_RDONLY);
	char	*line;

	while (1)
	{
		line = get_next_line(fd1);
		printf("%s", line);
		line = get_next_line(fd2);
		printf("%s", line);
		line = get_next_line(fd3);
		printf("%s", line);
		line = get_next_line(fd4);
		printf("%s", line);
		line = get_next_line(fd5);
		printf("%s", line);
		if (!line)
			break;
		free(line);
	}
	return (0);
}

