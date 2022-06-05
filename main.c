/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 13:02:14 by vsergio           #+#    #+#             */
/*   Updated: 2022/06/05 13:02:14 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
	int fd = open("ola.txt", O_RDONLY);
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		printf("%s", line);
		if (!line)
			break;
		free(line);
	}
	return (0);
}

