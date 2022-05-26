/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 11:01:02 by vsergio           #+#    #+#             */
/*   Updated: 2022/05/25 17:37:27 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"
#include <sys/fcntl.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

char	*get_next_line(int fd)
{
	char	*buffer_read;
	static	char	*stash;
	if(fd < 0)
	{
		printf("Failed to read the file");
		return (NULL);
	}
	read(fd, buffer_read, BUFFER_SIZE);
	buffer_read[BUFFER_SIZE] = '\0';
	return (0);
}
