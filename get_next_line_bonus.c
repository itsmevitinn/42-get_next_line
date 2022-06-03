/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 11:01:02 by vsergio           #+#    #+#             */
/*   Updated: 2022/06/02 15:01:57 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_list	*stash[1024];
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_and_stash(&stash[fd], fd);
	if (stash[fd] == NULL)
		return (NULL);
	extract_line(stash[fd], &line);
	clean_stash(&stash[fd]);
	if (line[0] == '\0')
	{
		free_stash(stash[fd]);
		stash[fd] = NULL;
		free(line);
		return (NULL);
	}
	return (line);
}

void	read_and_stash(t_list **stash, int fd)
{
	char	*buffer;
	int		readed;

	readed = 1;
	while (!found_newline(*stash) && readed != 0)
	{
		buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buffer == NULL)
			return ;
		readed = read(fd, buffer, BUFFER_SIZE);
		if ((*stash == NULL && readed == 0) || readed == -1)
		{
			free(buffer);
			return ;
		}
		buffer[readed] = '\0';
		add_to_stash(stash, buffer, readed);
		free(buffer);
	}
}

void	add_to_stash(t_list **stash, char *buffer, int readed)
{
	int		i;
	t_list	*end_stash;
	t_list	*new_node;

	i = 0;
	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return ;
	new_node->string = malloc(sizeof(t_list) * (readed + 1));
	if (new_node->string == NULL)
		return ;
	new_node->next = NULL;
	while (buffer[i] && i < readed)
	{
		new_node->string[i] = buffer[i];
		i++;
	}
	new_node->string[i] = '\0';
	if (*stash == NULL)
	{
		*stash = new_node;
		return ;
	}
	end_stash = ft_lstlast(*stash);
	end_stash->next = new_node;
}

void	extract_line(t_list *stash, char	**line)
{
	int	i;
	int	j;

	if (stash == NULL)
		return ;
	generate_line(stash, line);
	j = 0;
	if (*line == NULL)
		return ;
	while (stash)
	{
		i = 0;
		while (stash->string[i])
		{
			if (stash->string[i] == '\n')
			{	
				(*line)[j++] = stash->string[i];
				break ;
			}
			(*line)[j++] = stash->string[i++];
		}
		stash = stash->next;
	}
	(*line)[j] = '\0';
}

void	clean_stash(t_list **stash)
{
	t_list	*new;
	t_list	*last;
	int		i;
	int		j;

	j = 0;
	new = malloc(sizeof(t_list));
	if (stash == NULL || new == NULL)
		return ;
	last = ft_lstlast(*stash);
	i = 0;
	while (last->string[i] && last->string[i] != '\n')
		i++;
	if (last->string && last->string[i] == '\n')
		i++;
	new->string = malloc(sizeof(char) * ((ft_strlen(last->string) - i) + 1));
	new->next = NULL;
	if (new->string == NULL)
		return ;
	while (last->string[i])
		new->string[j++] = last->string[i++];
	new->string[j] = '\0';
	free_stash(*stash);
	*stash = new;
}
