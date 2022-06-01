/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 10:59:58 by vsergio           #+#    #+#             */
/*   Updated: 2022/06/01 14:38:03 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

typedef struct s_list
{
	char			*string;
	struct s_list	*next;
	int				fd;
}					t_list;

char	*get_next_line(int fd);
void	read_and_stash(t_list **stash, int fd);
void	add_to_stash(t_list **stash, char *buffer, int readed);
void	extract_line(t_list *stash, char **line);
void	clean_stash(t_list **stash);
int		found_newline(t_list *stash);
t_list	*ft_lstlast(t_list *stash);
void	generate_line(t_list *stash, char	**list);
void	free_stash(t_list *stash);
int		ft_strlen(const char *str);
#endif
